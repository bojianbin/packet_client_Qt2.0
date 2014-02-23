#include"mythread.h"
#include"bo.h"
#include"ffmtool.h"
#include"sock.h"
#include"pre_main.h"
#include<QtGui>

mythread::mythread(){

    ip = (char *)malloc(20);
    port = -1;
    ready = NULL;
    size = 0;

    stop_thread = false;

    heart = 50;
    ask = -1;
    resend = -1;

    ready_to_go = false;

}

void mythread::setprot(QString ip_ , QString port_){

    memcpy(ip,ip_.toAscii().data(),ip_.toAscii().size()+1);
    port =  port_.toInt();
    printf("%s\n",ip);
    printf("%d\n",port);
}

void mythread::heart_beat(){

    time_lock.lock();
    if(heart > 0) heart--;
    if(ask >0) ask--;
    if(resend >0) resend--;
    time_lock.unlock();
    return;
}
void mythread::stopp(){

    ready_lock.lock();
    stop_thread = true;
    ready_lock.unlock();
}
void mythread::showmessage(QString str){
    QString pre;
    pre =  QString(ip) + "::" +QString::number(port) + "  ";
    pre = pre + str;
    emit showmess(pre);
}
void mythread::run(){


    int PACK_SIZE;
    struct chip_queue QUEUE;
    struct codec_need needs = {640,480,10,5,0,30000};
    struct sockaddr_in servaddr;


    BUF = (char *)malloc(1000);
    PACK_BUF = (char *)malloc(100000);
    uint32_t NOWFRAME;//当前的frame号
    /////////////////////////////各个定时结果

    //////////////////////////////



    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,(struct sockaddr *)&(servaddr.sin_addr));
    servaddr.sin_port = htons(port);

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    ::connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    queue_init(&QUEUE);
    av_register_all();
    av_open_codec();


    if(start_connet(sockfd,500000) <0)
        //err_quit("start_connect error\n");
        showmessage("start_connect error");
    else showmessage("connect successfully");
    time_lock.lock();
    ask = 1;//设置重新发送时间
    time_lock.unlock();

    ready = (uint8_t *)malloc(640*480*3);
    getvideo = false;
    needtail = false;

    while(1){

        stop_lock.lock();
END:            if(stop_thread == true){//线程关闭

            free(BUF);
            free(PACK_BUF);
            //err_print("closed");
            chip_destroy(&QUEUE);
            showmessage("closed");
            codec_close(needs.bit_rate);
            ready_lock.lock();
            free(ready);
            free(ip);
            ready_lock.unlock();
            stop_lock.unlock();

            break;
        }
        stop_lock.unlock();
        int n;struct buf_chip tmpchip;
        uint8_t key;

        {//如果到了时间就发送心跳函数
            char ch;int j;
            ch = 0x80;
            time_lock.lock();
            if(heart == 0){
                //err_print("send heart beat signal\n");
                showmessage("send heart beat signal");
                j = sendto(sockfd,&ch,1,0,NULL,0);
                if(j < 0 )
                    //err_print("heart_beat error\n");
                    showmessage("heart_beat error");
                heart = 50;
            }
            time_lock.unlock();

        }
        {//检查是否需要重新发送“请求报文”
            time_lock.lock();
            if(ask == 0){
                //err_print("请求报文超时，并重新发送\n");
                showmessage("请求报文超时，并重新发送");
                start_connet(sockfd,30000);
                ask = 1;
            }
            time_lock.unlock();

        }
        {

        }
        ///////////////////////////////////////////////////////////////////////////////////////
        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
        n = recvfrom(sockfd,BUF,1000,0,NULL,NULL);
        if(n < 0 ){
            stopp();
            goto END;
        }

        key = protocol_handle(BUF);

        if(  key == 1){//数据帧
            //err_print("数据帧\n");
            char *ch;
            /*     if( !chip_empty(&QUEUE) && (htonl( *(uint32_t *)(BUF+1) ) != chip_top_time(&QUEUE) ) ){


                    if(syn_time(&needs) == -1){//发送延迟报文
                       send_delay(sockfd);
                    }

                    chips_to_buf(&QUEUE,PACK_BUF,&PACK_SIZE);
                    to_image(PACK_BUF,PACK_SIZE,&needs);
                    show();
                }*/

            ch = (char *)malloc(n-9);
            tmpchip.time = ntohl( *(uint32_t *)(BUF+1) );
            tmpchip.time2 = ntohl(  *(int *)(BUF+5)  );
            memcpy(ch,BUF+9,n-9);
            tmpchip.buf = ch;
            tmpchip.size = n-9;
            //   chip_push(&QUEUE,tmpchip);
            if(NOWFRAME != tmpchip.time){
                //队列中有上一帧数据的情况下收到了下一帧的数据，此时显示上一帧
                //并存入下一帧的第一条报文
                err_print("完整的数据帧\n");
                // emit showmess("完整的数据帧");

                if(tmpchip.time < NOWFRAME && tmpchip.time != 0)
                    continue;

                if(syn_time(&needs) == -1){//发送延迟报文
                    send_delay(sockfd);
                }

                chips_to_buf(&QUEUE,PACK_BUF,&PACK_SIZE);
                {//录制
                    video_lock.lock();
                    if(getvideo == true && needtail == false)
                        save_video(filename);
                    if(getvideo == false && needtail == true)
                        save_tail();
                    video_lock.unlock();
                }//录制
                ready_lock.lock();
                to_image(PACK_BUF,PACK_SIZE,&needs,&ready,&size);
                ready_to_go = true;
                ready_lock.unlock();

                chip_push(&QUEUE,tmpchip);
                NOWFRAME = tmpchip.time;
            }
            else{

                chip_push(&QUEUE,tmpchip);
                NOWFRAME = tmpchip.time;
            }


            if( chip_entity(&QUEUE)== 0  ){//que中已有完整报文

                if(syn_time(&needs) == -1){//发送延迟报文
                    send_delay(sockfd);
                }

                chips_to_buf(&QUEUE,PACK_BUF,&PACK_SIZE);

                ready_lock.lock();
                to_image(PACK_BUF,PACK_SIZE,&needs,&ready,&size);
                ready_to_go = true;
                ready_lock.unlock();
            }


        }//数据帧
        if(key == 2){//服务器应答
            int old;
            //err_print("收到“应答报文”\n");
            showmessage("收到应答报文");
            time_lock.lock();
            ask = -1;//收到服务器回应，则取消“要求”报文重发
            time_lock.unlock();
            old = needs.bit_rate;

            needs.width  = ntohl( *(int *)(BUF+1) );
            needs.height = ntohl( *(int *)(BUF+5) );
            needs.fps    = ntohl( *(int *)(BUF+9) );
            needs.gopsize= ntohl( *(int *)(BUF+13));
            needs.max_b_frames= ntohl( *(int *)(BUF+17));
            needs.bit_rate=ntohl( *(int *)(BUF +25));
            showmessage(QString("width:%1 height %2 fps:%3 gopsize:%4 max_b_frames:%5 bit_rate:%6")\
                        .arg(needs.width).arg(needs.height).arg(needs.fps).arg(needs.gopsize).arg(needs.max_b_frames)\
                        .arg(needs.bit_rate));


            //if( old != needs.bit_rate)
            //  codec_close(needs.bit_rate);


        }



    }//while(1)


}

/**
 * ��֤����select���������fd_set��select_client.cpp
 * zhangyl 2018.12.24
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000

int main(int argc, char* argv[])
{
    //����һ��socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //���ӷ�����
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    fd_set readset;
    FD_ZERO(&readset);

    //������socket���뵽�����Ŀɶ��¼���ȥ
    FD_SET(clientfd, &readset);
    timeval tm;
    tm.tv_sec = 5;
    tm.tv_usec = 0;
    int ret;
    int count = 0;
    fd_set backup_readset;
    memcpy(&backup_readset, &readset, sizeof(fd_set)); // hbsun:���ݣ�������û�б仯��
    while (true)
    {
        if (memcmp(&readset, &backup_readset, sizeof(fd_set)) == 0)
        {
            std::cout << "equal" << std::endl;
        }
        else
        {
            std::cout << "not equal" << std::endl;
        }

        //����ֻ���ɶ��¼���������д���쳣�¼�
        ret = select(clientfd + 1, &readset, NULL, NULL, &tm);
        std::cout << "tm.tv_sec: " << tm.tv_sec << ", tm.tv_usec: " << tm.tv_usec << std::endl;
        if (ret == -1)
        {
            //���˱��ź��жϵ����Σ�����������ǳ���
            if (errno != EINTR)
                break;
        } else if (ret == 0){
            //select������ʱ
            std::cout << "no event in specific time interval, count��" << count << std::endl;
            ++count;
            continue;
        } else {
            if (FD_ISSET(clientfd, &readset))
            {
                //��⵽�ɶ��¼�
                char recvbuf[32];
                memset(recvbuf, 0, sizeof(recvbuf));
                //����Զ˷����ݵ�ʱ�򲻳���31���ַ���
                int n = recv(clientfd, recvbuf, 32, 0);
                if (n < 0)
                {
                    //���˱��ź��жϵ����Σ�����������ǳ���
                    if (errno != EINTR)
                        break;
                } else if (n == 0) {
                    //�Զ˹ر�������
                    break;
                } else {
                    std::cout << "recv data: " << recvbuf << std::endl;
                }
            }
            else
            {
                std::cout << "other socket event." << std::endl;
            }
        }
    }

    //�ر�socket
    close(clientfd);

    return 0;
}
/*************************************************************      
    FileName : serialport.c  
    FileFunc : ����ʵ���ļ�    
    Version  : V0.1      
    Author   : Sunrier      
    Date     : 2012-06-13 
    Descp    : Linux��ʵ�ִ��ڿ�    
*************************************************************/   
/*#include "serialport.h"*/  
#include <stdio.h>  
#include <strings.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <termios.h>  
  
int open_port(char *dev)  
{  
    int fd = -1;  
      
    fd = open(dev, O_RDWR|O_NOCTTY|O_NDELAY);  
    if(fd < 0) {  
        perror("Can't Open Serial Port !");  
        return (-1);  
    } else {  
        printf("Open %s ok\n",dev);  
    }  

    if(fcntl(fd, F_SETFL,0)<0 ) {  
        printf("fcntl failed !\n");  
        return (-1);  
    } else {  
        printf("fcntl = %d !\n",fcntl(fd,F_SETFL,0));  
    }  
      
    if( !isatty(fd) ) {  
        printf("Standard input isn't a terminal device !\n");  
        return (-1);  
    } else {  
        printf("It's a serial terminal device!\n");  
    }  
	  
    printf("open_port file ID= %d !\n",fd);  
      
    return fd;  
      
}  
  
int set_port(int fd,int iBaudRate,int iDataSize,char cParity,int iStopBit)  
{  
    int iResult = 0;  
    struct termios oldtio,newtio;  
      
      
    iResult = tcgetattr(fd,&oldtio);/*����ԭ�ȴ�������*/  
    if( iResult )  
    {  
        perror("Can't get old terminal description !");  
        return (-1);  
    }  
      
      
    bzero(&newtio,sizeof(newtio));  
    newtio.c_cflag |= CLOCAL | CREAD;/*���ñ������Ӻͽ���ʹ��*/  
      
    /*�����������������*/  
    switch( iBaudRate )  
    {  
        case 2400:  
                            cfsetispeed(&newtio,B2400);  
                            cfsetospeed(&newtio,B2400);  
                            break;  
        case 4800:  
                            cfsetispeed(&newtio,B4800);  
                            cfsetospeed(&newtio,B4800);  
                            break;    
        case 9600:  
                            cfsetispeed(&newtio,B9600);  
                            cfsetospeed(&newtio,B9600);  
                            break;    
        case 19200:  
                            cfsetispeed(&newtio,B19200);  
                            cfsetospeed(&newtio,B19200);  
                            break;  
        case 38400:  
                            cfsetispeed(&newtio,B38400);  
                            cfsetospeed(&newtio,B38400);  
                            break;    
        case 57600:  
                            cfsetispeed(&newtio,B57600);  
                            cfsetospeed(&newtio,B57600);  
                            break;                                                        
        case 115200:  
                            cfsetispeed(&newtio,B115200);  
                            cfsetospeed(&newtio,B115200);  
                            break;    
        case 460800:  
                            cfsetispeed(&newtio,B460800);  
                            cfsetospeed(&newtio,B460800);  
                            break;                        
        default     :  
                            /*perror("Don't exist iBaudRate !");*/  
                            printf("Don't exist iBaudRate %d !\n",iBaudRate);  
                            return (-1);                                                                      
    }  
      
    /*��������λ*/  
    newtio.c_cflag &= (~CSIZE);  
    switch( iDataSize )  
    {  
        case    7:  
                        newtio.c_cflag |= CS7;  
                        break;  
        case    8:  
                        newtio.c_cflag |= CS8;  
                        break;  
        default:  
                        /*perror("Don't exist iDataSize !");*/  
                        printf("Don't exist iDataSize %d !\n",iDataSize);  
                        return (-1);                                  
    }  
      
    /*����У��λ*/  
    switch( cParity )  
    {  
        case    'N':                    /*��У��*/  
                            newtio.c_cflag &= (~PARENB);  
                            break;  
        case    'O':                    /*��У��*/  
                            newtio.c_cflag |= PARENB;  
                            newtio.c_cflag |= PARODD;  
                            newtio.c_iflag |= (INPCK | ISTRIP);  
                            break;  
        case    'E':                    /*żУ��*/  
                            newtio.c_cflag |= PARENB;  
                            newtio.c_cflag &= (~PARODD);  
                            newtio.c_iflag |= (INPCK | ISTRIP);  
                            break;                
        default:  
                            /*perror("Don't exist cParity  !");*/  
                            printf("Don't exist cParity %c !\n",cParity);  
                            return (-1);                                  
    }  
      
    /*����ֹͣλ*/  
    switch( iStopBit )  
    {  
        case    1:  
                        newtio.c_cflag &= (~CSTOPB);  
                        break;  
        case    2:  
                        newtio.c_cflag |= CSTOPB;  
                        break;  
        default:  
                        /*perror("Don't exist iStopBit !");*/  
                        printf("Don't exist iStopBit %d !\n",iStopBit);  
                        return (-1);                                  
    }  
      
    newtio.c_cc[VTIME] = 0; /*���õȴ�ʱ��*/  
    newtio.c_cc[VMIN] = 0;  /*������С�ַ�*/  
    tcflush(fd,TCIFLUSH);       /*ˢ���������(TCIOFLUSHΪˢ�������������)*/  
    iResult = tcsetattr(fd,TCSANOW,&newtio);    /*�����µ�����ʹ֮��Ч,����TCSANOW��ʾ������������*/  
  
    if( iResult )  
    {  
        perror("Set new terminal description error !");  
        return (-1);  
    }     
      
    printf("set_port success !\n");  
      
    return 0;  
}  
  
int read_port(int fd,void *buf,int iByte)  
{  
    int iLen = 0;  
    if( !iByte )  
    {  
        printf("Read byte number error !\n");  
        return iLen;  
    }  
      
    iLen = read(fd,buf,iByte);  
      
    return iLen;  
}  
  
int write_port(int fd,void *buf,int iByte)  
{  
    int iLen = 0;  
    if( !iByte )  
    {  
        printf("Write byte number error !\n");  
        return iLen;  
    }  
      
    iLen = write(fd,buf,iByte);  
      
    return iLen;  
}  
  
  
int close_port(int fd)  
{  
    int iResult = -1;  
      
    iResult = close(fd);  
      
    return iResult;  
}  

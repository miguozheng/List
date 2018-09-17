#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdarg.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/epoll.h>

#include "list.h"

/***************************************************************************************************************************************************
*
*function declear
*
****************************************************************************************************************************************************/
void va_func_test(char *pstr,...);
void SoundListQueueInit(void);
gint glib_insert_comprise_func(void *p0,void *p1);
void print_glist(GList *ptemp);
void glib_test1(void);
void ptest(char **p);
void timer_test(void);
/***************************************************************************************************************************************************
*
*varlue declear
*
****************************************************************************************************************************************************/

static gint values_test = 0;  
static gboolean boolen_value = FALSE;  
static gchar *str_test; 


static GOptionEntry entries[] =  
{  
  { "vaule", 'v', 0, G_OPTION_ARG_INT, &values_test, "Average over N repetitions", "N" },  
  { "boolen_value", 'b', 0, G_OPTION_ARG_NONE, &boolen_value, "Be verbose", NULL },  
  { "str_test", 's', 0, G_OPTION_ARG_STRING, &str_test, "test the stirng", NULL},
  {NULL} 
};  


typedef union
{
	UINT8 	uint8data;
	UINT16  uint16data;
	UINT32  uint32data;
	UINT8   buf[4];
}union_test;
extern Node SoundListMem[31];
extern UINT8 ListMenMan[31];
DList SoundDlist;
char testchar[] = "Hello Miguo!";

/***************************************************************************************************************************************************
*
*self-def list test
*
****************************************************************************************************************************************************/

void SoundListQueueInit(void)
{
	UINT8 i;
	
	for(i = 0;i < 30+1;i++){
		ListMenMan[i] = 0;
		SoundListMem[i].Data = NULL;
		SoundListMem[i].MemIterm = 0xFF;
		SoundListMem[i].Previous = NULL;
		SoundListMem[i].Next = NULL;
	}
	listInit(&SoundDlist,30+1);
}
/***************************************************************************************************************************************************
*
*glib list test
*
****************************************************************************************************************************************************/

gint glib_insert_comprise_func(void *p0,void *p1)
{
	gint re=0;
	printf("p0= %s,p1= %s\n",p0,p1);
	if(*((gint *)p0) == *((gint *)p1)){
		re = 0;
	}else if(*((gint *)p0) > *((gint *)p1)){
		re = 2;
	}else if(*((gint *)p0) < *((gint *)p1)){
		re = -1;
	}
	printf("re= %d\n",re);
	return re;
}
void print_glist(GList *ptemp)
{
	GList *temp = ptemp;
	for(;;){
		if(temp){
			if(temp->data){
				printf("The first item is %s\n",temp->data);
			}
			temp=temp->next;
		}else{
			printf("List NULL\n");
			break;
		}
	}
}
void glib_test1(void)
{
	gint i;
	GList *list=0,*temp=0,*copylist=0;
	list=g_list_append(list,"AA\n");
	list=g_list_append(list,"BB\n");
	list=g_list_append(list,"CC\n");
	list=g_slist_prepend(list,"DD\n");
	list=g_slist_insert(list,"EE\n",3); 
	list=g_slist_insert_before(list,list,"FF\n");
	list=g_slist_insert_sorted(list,"GG\n",glib_insert_comprise_func);
	print_glist(list);
	list=g_slist_remove(list,"EE\n");
	print_glist(list);	
	temp = list->next;
	//list=g_slist_remove_link(list,temp); 
	list=g_slist_delete_link (list,temp); 
	print_glist(list);	
	if(temp->data){
		printf("temp->data=%s\n",temp->prev);
	}else{
		printf("temp->data=NULL\n");
	}
	copylist=g_slist_copy(list);
	printf("Print copy list:\n");
	print_glist(copylist);	
	
}
/***************************************************************************************************************************************************
*
*mult vaule function test
*
****************************************************************************************************************************************************/

void va_func_test(char *pstr,...)
{
	va_list args;
	char *printfstr = NULL;
	gint i = 0;
	if(pstr){
		printf("%s print start!!!\n",pstr);
	}else{
		printf("pstr NULL!!!\n");
		return;
	}
	va_start(args,pstr);
	while(1){
		printfstr = va_arg(args,char *);
		if((*printfstr) == 'e'){
			printf("va_func_test print finish!!!\n");
			break;
		}else{
			i++;
			printf("va_func_test print %d :%s\n",i,printfstr);
		}
	}
	va_end(args);
}
/***************************************************************************************************************************************************
*
*pthread test
*
****************************************************************************************************************************************************/

void thread_1_test(void *argv)
{
	char getchart[50];
	gint i = 0;
	struct timespec ts;
	
	while(1){
		printf("I'm thread 1,runing times = %d\n",i++);	
		if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
			g_print("realtime error!\n");
		}else{
			g_print("I'm thread 1,. ts.tv_nsec = %d; ts.tv_sec = %d.\n",ts.tv_nsec,ts.tv_sec);
		}
		usleep(1);
		if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
			g_print("realtime error!\n");
		}else{
			g_print("I'm thread 1,. ts.tv_nsec = %d; ts.tv_sec = %d.\n",ts.tv_nsec,ts.tv_sec);
		}

		sleep(2);
		
	}
}
void thread_2_test(void *argv)
{
	gint i = 0;
	
	while(1){
		printf("I'm thread 2,runing times = %d\n",i++);	
		sleep(4);
	}
}
pthread_t id1,id2;
void thread_test(void)
{
	int ret=0;
	
    ret=pthread_create(&id1,NULL,(void*)thread_1_test,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
    }
    ret=pthread_create(&id2,NULL,(void*)thread_2_test,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
    }
   //pthread_join(id1,NULL);
   //pthread_join(id2,NULL);
}
/***************************************************************************************************************************************************
*
*main loop and gtimer test
*
****************************************************************************************************************************************************/

gboolean callback(gpointer arg)
{
	struct timespec ts;
	if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        g_print("realtime error!\n");
    }else{
		g_print("test time out. ts.tv_nsec = %d; ts.tv_sec = %d.\n",ts.tv_nsec,ts.tv_sec);
	}
}

GMainLoop* loop;

void timer_test(void)
{
	
    if(g_thread_supported() == 0)
    g_thread_init(NULL);
    g_print("g_main_loop_new\n");
    loop = g_main_loop_new(NULL, FALSE);
	if(loop){
		printf("main loop creat ok!\n");
	}
    g_timeout_add(5000,callback,NULL);
    g_print("g_main_loop_run\n");
    g_main_loop_run(loop);
    g_print("g_main_loop_unref\n");
    g_main_loop_unref(loop);
}
/***************************************************************************************************************************************************
*
*g_context test
*
****************************************************************************************************************************************************/

char pmigo[] = "Migo,papa love you";
void ptest(char **p)
{
	*p = pmigo;
}

void test_g_opnion_entry(int argc, char *argv[])
{
  GError *error = NULL;  
  GOptionContext *context;  
  context = g_option_context_new ("- test migo model performance");//  
  if(context){
	  g_option_context_add_main_entries (context, entries, NULL);  //添加列表
	  g_option_context_set_summary(context, "migo detail" );
	  //g_option_context_set_help_enabled(context,TRUE);
	  // g_option_context_add_group (context, gtk_get_option_group (TRUE));  
	  if (!g_option_context_parse (context, &argc, &argv, &error))	//执行命令赋值
		{  
		  g_print ("option parsing failed: %s/n", error->message);	
		} 
  }
 
}
/***************************************************************************************************************************************************
*
*g_key_file test
*
****************************************************************************************************************************************************/
#define FILE_PATH "/mnt/hgfs/nbt/list/test.migo"
void conf_file_test(void)
{
	GKeyFile *file_key = NULL;
    GKeyFileFlags flags = G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS;
    GError *error = NULL;
    gchar *tmp_str = NULL;
	gint temp_int;

	file_key = g_key_file_new();
    if(FALSE == g_key_file_load_from_file(file_key, FILE_PATH, flags, &error)) {//�Ѵ����ϵ������ļ����ص�������
	    g_key_file_free(file_key);
	}
	temp_int = g_key_file_get_integer(file_key,"MIGO","migo_x",NULL);
	printf("\nmigo_x = %d\n",temp_int);//	g_key_file_get_value()
	tmp_str = g_key_file_get_string(file_key,"MIGO","migo_y",NULL);
	printf("\nmigo_y = %s\n",tmp_str);//	g_key_file_get_value()
	tmp_str = g_key_file_get_string(file_key,"MIGO","migo_boolen",NULL);
	printf("\migo_boolen = %s\n",tmp_str);//	g_key_file_get_value()
	tmp_str = g_key_file_get_string(file_key,"MIGO","migo_long",NULL);
	printf("\migo_long = %s\n",tmp_str);//	g_key_file_get_value()
	tmp_str = g_key_file_get_string(file_key,"MIGO","migo_float",NULL);
	printf("\migo_float = %s\n",tmp_str);//	g_key_file_get_value()
	tmp_str = g_key_file_get_string(file_key,"PATH","bin_path",NULL);
	printf("\bin_path = %s\n",tmp_str);//	g_key_file_get_value()

	g_key_file_free(file_key);
}
/***************************************************************************************************************************************************
*
*fork_test
*
****************************************************************************************************************************************************/
static char *icuDisplayUi_env[] = {
	NULL,
	"migo,papa love you",
	"migo is a good boy",
	"migo,start eat food",
	"migo,is so cute",
	"migo,is my son",
	"migo,is playing",
	NULL
};

void fork_test(void)
{
    pid_t pid;
    char *name = NULL;

    name = "/mnt/hgfs/nbt/process1/Pro1";
    if(name) {
        icuDisplayUi_env[0] = name;
        pid = fork();
        if(0 == pid) {
			printf("\n~~~~~~~~creat process success!~~~~~~~~~~~~~%d\n",getpid());
            execv(name, icuDisplayUi_env);
            exit(-1);
        }else{
			printf("\n~~~~~~~~creat process failed!~~~~~~~~~~~~~~%d\n",getpid());
		}
    } 

}
/***************************************************************************************************************************************************
*
*sem_test
*
****************************************************************************************************************************************************/
pthread_t sem_id1,sem_id2;

sem_t sem_play;

void sem_thread_1_test(void *argv)
{
	char getchart[50];
	gint i = 0;
	struct timespec ts;
	
	while(1){
		printf("Hello,sem_thread_1_test, I posted sem signal %d times!\n",i++);	
		sem_post(&sem_play);
		sem_post(&sem_play);
		sleep(5);
		
	}
}
void sem_thread_2_test(void *argv)
{
	unsigned long msec = 5000;
	gint i = 0;
	struct timespec ts;
	
	while(1){
		//sem_wait(&sem_play);
		msec = 5000;
		if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
			printf("get time error!\n");
        	return sem_wait(&sem_play);
    	}
		ts.tv_sec += msec / 1000;
		ts.tv_nsec += (msec % 1000) * 1000 * 1000;
		ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
		ts.tv_nsec = ts.tv_nsec %(1000 * 1000 * 1000);
		if(0 == sem_timedwait(&sem_play,&ts)){
			printf("Hi, sem_thread_0_test,I got the sem signal %d times!\n",i++);
		}
		//sem_timedwait(&ts,&sem_play);
			
		//sleep(1);
	}
}

void sem_test(void)
{
	int res;
	
	res = sem_init(&sem_play, 0, 5);
	
	if (0 != res)
	{
	 	printf("Semaphore initialization failed");
	}
	

	res = pthread_create(&sem_id1,NULL,(void*)sem_thread_1_test,NULL);
    if(res)
    {
        printf("create sem-pthread error!\n");
    }
    res = pthread_create(&sem_id2,NULL,(void*)sem_thread_2_test,NULL);
    if(res)
    {
        printf("create sem-pthread error!\n");
    }
	
}
/***************************************************************************************************************************************************
*
*serialport_test
*
****************************************************************************************************************************************************/
pthread_t serialport_id1;
int serial_port_fd = -1;

void serialport_thread_1_test(void *argv)
{
	char getchart[1024];
	char sendchar[2] = {0x55,0xaa};
	gint i = 0;
	struct timespec ts;
	memset(getchart,0,1024);
	
	while(1){
		i = read_port(serial_port_fd,getchart,1024);
		if(i){
			
			printf("Ding,I got the serialport %d data:%s  \n",i,getchart);
			memset(getchart,0,1024);
			write_port(serial_port_fd,"self send test",15);
		}
		//write_port(serial_port_fd,sendchar,2);
		sleep(5);
		//printf("serialport_thread_1_test Live  \n");
		
	}
}


void serialport_test(char *port_name)
{
	int fd = -1,res;

	if(!port_name){
		return;
	}
	fd = open_port(port_name);
	if(-1 == fd){
		printf("Open serialport %s failed\n",port_name);
	}else{
		serial_port_fd = fd;
		printf("serial_port_fd =  %d.\n",serial_port_fd);
		if(set_port(fd,115200,8,'N',1)){
			printf("Set serialport %s failed\n",port_name);
		}else{
			write_port(serial_port_fd,"serial test!",13);
			res = pthread_create(&serialport_id1,NULL,(void*)serialport_thread_1_test,NULL);
		    if(res)
		    {
		        printf("create sem-pthread error!\n");
		    }			
		}
		
	}
}
/***************************************************************************************************************************************************
*
*epoll for serialport_test
*
****************************************************************************************************************************************************/
pthread_t epoll_thread_id1;
int epoll_serial_port_fd = -1;
int epoll_id;
struct epoll_event epoll_event;
struct epoll_event epoll_events[10];

void epoll_thread_test(void *argv)
{
	char getchart[1024];
	char sendchar[2] = {0x55,0xaa};
	gint i = 0;
	struct timespec ts;
	memset(getchart,0,1024);
	
	printf("begin recive!\n");
	while(1){
		i = epoll_wait(epoll_id, epoll_events, 1, 50);
		//printf("epoll event = %i.\n",i);
		if(i > 0){
			printf("epoll event = %i.\n",i);
			i = read_port(epoll_serial_port_fd,getchart,1024);
			if(i){
				printf("Ding,I got the serialport %d data:%s  \n",i,getchart);
				memset(getchart,0,1024);
				//write_port(epoll_serial_port_fd,"self send test",15);
			}		

		}
	}
}

void epoll_for_serialport_test(char *port_name)
{

	int fd = -1,res;
	
	//init serial
	fd = open_port(port_name);
	if(-1 == fd){
		printf("Open serialport %s failed\n",port_name);
	}else{
		epoll_serial_port_fd = fd;
		printf("serial_port_fd =  %d.\n",epoll_serial_port_fd);
		if(set_port(fd,115200,8,'N',1)){
			printf("Set serialport %s failed\n",port_name);
		}else{
			write_port(epoll_serial_port_fd,"serial test!",13);
			
		}
		
	}
	//init epoll
	epoll_id = epoll_create1(0);
	if(epoll_id < 0){
		printf("creat epoll fialed !\n");
	}
	else{
		printf("EPOLL ID id %d .\n",epoll_id);
		
		epoll_event.events = EPOLLET | EPOLLIN;
		epoll_event.data.fd = epoll_serial_port_fd;
	
	
		if(epoll_ctl(epoll_id, EPOLL_CTL_ADD, epoll_serial_port_fd, &epoll_event) < 0){
			printf("set EPOLL fialed.\n");
		}
	}
	//creat thread
	res = pthread_create(&epoll_thread_id1,NULL,(void*)epoll_thread_test,NULL);
	if(res)
	{
		printf("create epoll-pthread error!\n");
	}

}
//
/***************************************************************************************************************************************************
*
*main
*
****************************************************************************************************************************************************/


int main(int argc,char *argv[])
{
	Node *pnode = NULL;
	GList* list = 0;
	char *ptempmigo = NULL;
	char getchart[50];
	union_test uniondata;

    list = g_list_append(list,argv[1]);
    printf("The first item is %s\n",list->data);
	SoundListQueueInit();
	pnode = listNodeMake((void *)argv[1]);
	printf("pnode:%p\n",pnode);
	//printf("%s\n",(char *)pnode->Data);
	listNodeInsertQueue(&SoundDlist,pnode);
	pnode = listGetTial(&SoundDlist);
	printf("head:%p\n",pnode);
	printf("Welcome:%s\n",(char *)pnode->Data);
	g_printf("Hello world!\n");
	
	//glib_test1();
	//va_func_test(argv[0],argv[1],argv[2],argv[3],argv[4]);
	
	ptest(&ptempmigo);	
	printf("**p = :%s\n",ptempmigo);

	uniondata.uint32data = 0x44332211;
	printf("uint32data = %8x;  uint16data = %8x;  uint8data = %8x;  \n",uniondata.uint32data,uniondata.uint16data,uniondata.uint8data);
	printf("buf[0] = %2x;  buf[1] = %2x;  buf[2] = %2x; buf[3] = %2x; \n",uniondata.buf[0],uniondata.buf[1],uniondata.buf[2],uniondata.buf[3]);
	if(0x44 == uniondata.buf[0]){
		printf("\n\nBig-Endian mode.\n\n");
	}else{
		printf("\n\nLittle-Endian mode.\n\n");
	}
	//printf("put some words...\n");
	//gets(getchart);
	//printf("th get char : %s\n",getchart);

	
	printf("brfore..values_test = %d; boolen_value = %d; str_test : %s\n",values_test,boolen_value,str_test);
	//启动入参给变量赋值
	test_g_opnion_entry(argc,argv);
	printf("values_test = %d; boolen_value = %d; str_test : %s\n",values_test,boolen_value,str_test);
	//配置文件给变量赋值
	conf_file_test();

	//fork_test();

	//thread_test();
	
	//sem test
	//sem_test();	

	//serialport test
	//serialport_test(argv[1]);
	
	//epoll for serial test
	epoll_for_serialport_test(argv[1]);
	
	//timer_test();
	while(1);

	return 0;
}

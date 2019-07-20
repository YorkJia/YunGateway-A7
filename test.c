#include <unp.h>
#include <bsp.h>


#include <sqlite3.h>

static void *dev_thread(void *arg);

sqlite3 *gDb = NULL;


typedef struct member{
	int index;
        char name[32];
	char driver[16];
	int rem_para1;
	char rem_para2[16];
	char rem_para3[16];
        char loc_para1[16];
	char loc_para2[16];
	int com_index;
	int data_type;
	char rw_type[3];
	char unit_para1[3];
	char unit_para2[3];
	int data_para;
	int start_addr;
	int unit_len;
	int data_hold;
	int scan_cycle;
	int log; 
	int repeat;
} DEV_PARA;



static void *dev_thread(void *arg)
{
	DEV_PARA *pdev;

	pdev = (DEV_PARA *)arg;
	
	Pthread_detach(pthread_self());

	while(1){

		printf("%d|", pdev->index);
		printf("%s|", pdev->name);
		printf("%s|", pdev->driver);
		printf("%d|", pdev->rem_para1);
		printf("%s|", pdev->rem_para2);
		printf("%s|", pdev->rem_para3);
		printf("%s|", pdev->loc_para1);
		printf("%s|", pdev->loc_para2);
		printf("%d|", pdev->com_index);
		printf("%d|", pdev->data_type);
		printf("%s|", pdev->rw_type);
		printf("%s|", pdev->unit_para1);
		printf("%s|", pdev->unit_para2);
		printf("%d|", pdev->data_para);
		printf("%d|", pdev->start_addr);
		printf("%d|", pdev->unit_len);
		printf("%d|", pdev->data_hold);
		printf("%d|", pdev->scan_cycle);
		printf("%d|", pdev->log); 
		printf("%d\n", pdev->repeat);

		sleep(2);
	}
		return 0;
}



int
main(void)
{
	int i, nCol;
	sqlite3_stmt *pstmt;
	const char *pzTail;	

	DEV_PARA *thread_para;
	pthread_t tid[10];
	int dev_index = 0;
	int cnt = 0;
	
	thread_para = (DEV_PARA *)malloc(sizeof(DEV_PARA)*10);
	/* open the database. */
	Sqlite3_open("cfg.db", &gDb);

	/* sql dev table query.*/
	const char *sql = "SELECT* FROM dev;";
	Sqlite3_prepare_v2(gDb, sql, strlen(sql), &pstmt, &pzTail);

	while(sqlite3_step( pstmt ) == SQLITE_ROW){
		/*
		 * create a thread,then push a para point to the thread,
		 * the thread use the driver type,and other para to run
		*/
		nCol = 0;
		thread_para[dev_index].index = sqlite3_column_int(pstmt, nCol++);
		strcpy(thread_para[dev_index].name,sqlite3_column_text(pstmt, nCol++));
		printf("name:%s\n", thread_para[dev_index].name);
		strcpy(thread_para[dev_index].driver,sqlite3_column_text(pstmt, nCol++));
		thread_para[dev_index].rem_para1 = sqlite3_column_int(pstmt, nCol++);
		strcpy(thread_para[dev_index].rem_para2, sqlite3_column_text(pstmt, nCol++));
		strcpy(thread_para[dev_index].rem_para3, sqlite3_column_text(pstmt, nCol++));
		strcpy(thread_para[dev_index].loc_para1, sqlite3_column_text(pstmt, nCol++));
		strcpy(thread_para[dev_index].loc_para2, sqlite3_column_text(pstmt, nCol++));
		thread_para[dev_index].com_index = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].data_type = sqlite3_column_int(pstmt, nCol++);
		strcpy(thread_para[dev_index].rw_type, sqlite3_column_text(pstmt, nCol++));
		strcpy(thread_para[dev_index].unit_para1, sqlite3_column_text(pstmt, nCol++));
		strcpy(thread_para[dev_index].unit_para2, sqlite3_column_text(pstmt, nCol++));
		thread_para[dev_index].data_para = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].start_addr = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].unit_len = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].data_hold = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].scan_cycle = sqlite3_column_int(pstmt, nCol++);
		thread_para[dev_index].log = sqlite3_column_int(pstmt, nCol++); 
		thread_para[dev_index].repeat = sqlite3_column_int(pstmt, nCol++);
		dev_index++;
	}

	sqlite3_finalize(pstmt);
//	sqlite3_close(gDb);
	
	for(i = 0; i < 5; i++)	
		pthread_create(&tid[i], NULL, dev_thread, (void *)&thread_para[i]);



	while(1){
		cnt++;
		printf("the main app running:%d\n", cnt);
		sleep(5);
	}
	return 0;
}

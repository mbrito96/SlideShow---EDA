#include <stdio.h>
#include <stdlib.h>


#define APR_DECLARE_STATIC
#include "apr.h"
#include "apr_general.h"
#include "apr_pools.h"
#include "apr_file_io.h"

#define PATH "c:/windows/"
#define FILE_FLAGS (APR_FINFO_MTIME | APR_FINFO_CTIME | APR_FINFO_ATIME | APR_FINFO_SIZE | APR_FINFO_CSIZE | APR_FINFO_TYPE | APR_FINFO_USER | APR_FINFO_NAME)

int
main (int argc, char * argv[])
{

	char errorBufferString[1024];
	char timeBuffer[APR_CTIME_LEN];
	apr_pool_t * mainPool = NULL;
	apr_dir_t * mainDirectory = NULL;
	apr_finfo_t nextFileInfo; 
	apr_status_t dirReadStatus = APR_SUCCESS;
	if(argc == 2)
	{
		if (apr_app_initialize(&argc, &argv, NULL) == APR_SUCCESS)
		{

			if(apr_pool_create(&mainPool,NULL) == APR_SUCCESS)
			{

				if( apr_dir_open(&mainDirectory, argv[1],mainPool) == APR_SUCCESS)
				{
					printf("Directory %s Content:\n",argv[1]);
					while( ((dirReadStatus = apr_dir_read(&nextFileInfo,FILE_FLAGS,mainDirectory)) == APR_SUCCESS) || (dirReadStatus == APR_INCOMPLETE))
					{
						printf("%s\\%s",argv[1], nextFileInfo.name );
						if(nextFileInfo.valid & APR_FINFO_MTIME)
						{
							apr_ctime(timeBuffer, nextFileInfo.mtime);
							printf("\n\tModified: %s",timeBuffer);
						}
						if(nextFileInfo.valid & APR_FINFO_CTIME)
						{
							apr_ctime(timeBuffer, nextFileInfo.ctime);
							printf("\n\tCreated: %s",timeBuffer);
						}
						if(nextFileInfo.valid & APR_FINFO_ATIME)
						{
							apr_ctime(timeBuffer, nextFileInfo.atime);
							printf("\n\tLast Access: %s",timeBuffer);
						}
						if(nextFileInfo.valid & APR_FINFO_SIZE)
							printf("\n\tSize: %d",nextFileInfo.size);

						if(nextFileInfo.valid & APR_FINFO_CSIZE)
							printf("\n\tSize on disk: %d",nextFileInfo.csize);
						
						if(nextFileInfo.valid & APR_FINFO_TYPE)
							printf("\n\tType: %s",(nextFileInfo.filetype==APR_REG? ("Regular File"):(nextFileInfo.filetype==APR_DIR? ("Directory"):("Unknown Format"))));
						
						putchar('\n');

					}
				
					if(dirReadStatus != APR_ENOENT)
					{
						apr_strerror(dirReadStatus, errorBufferString,1024);	
						printf("Error %s reading directory %s, Error Number %d\n", errorBufferString, argv[1], dirReadStatus);
					}

					
					apr_dir_close(mainDirectory);
				}
				else
					printf("Unable to open %s\n",argv[1]);

				apr_pool_destroy(mainPool);
			}
			else
				printf("Error creating mainPool\n");

			apr_terminate();
		}
		else
			printf("Error Initializing APR\n");
	}
	else
	{
		printf("Wrong number of paramenters\n");
		printf("Call read Directory with the path for the directory you'd like to read\n");
		printf("Eg: readDirectory c:\\windows\\ \n");
	}
	system ("PAUSE");
	return 0;
}
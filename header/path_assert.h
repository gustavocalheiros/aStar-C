#ifndef __PATH_ASSERT_H__
#define __PATH_ASSERT_H__

#define ASSERT_OK(s) \
	{\
	if(s != OK)\
		printf("error:%s file:%s line: %d\n", \
			message(s), __FILE__, __LINE__); \
	}

#define ASSERT_NOT_NULL(pointer) \
	{\
		if(!pointer)\
		{\
			printf("NULL POINTER! aborting... file:%s line: %d\n", \
				__FILE__, __LINE__); \
				exit(EXIT_FAILURE); \
		}\
	}

#define ASSERT_REMOVE(s) \
	{\
	if(s != OK && s != ERRINDEX)\
		printf("error:%s file:%s line: %d\n", \
			message(s), __FILE__, __LINE__); \
	}

#endif //__PATH_ASSERT_H__

#include stdlib.h
#include stdio.h
#include systypes.h
#include sysipc.h
#include sysshm.h
#include string.h

#define SEGSIZE 100

main(int argc, char argv[])
    {
    	key_t key;
    	int shmid, cntr;
   	char segptr;

    	key = ftok(., 'S');
    shmid = shmget(key, SEGSIZE, IPC_CREATIPC_EXCL0666);
    shmid = shmget(key, SEGSIZE, 0);
    printf(Creating new shared memory segmentn);

    segptr = shmat(shmid, 0, 0);

    switch(tolower(argv[1][0]))
    {
   	 case 'w' writeshm(shmid, segptr, argv[2]);
  	  break;
   	 case 'r' readshm(shmid, segptr);
   	  break;
   	 case 'd' removeshm(shmid);
  	  break;
   	 case 'm' changemode(shmid, argv[2]);
  	  break;
    }
     }
    writeshm(int shmid, char segptr, char text)
    {
    strcpy(segptr, text);
    printf(Done...n);
    }
    readshm(int shmid, char segptr)
    {
    printf(segptr %sn, segptr);
    }
    removeshm(int shmid)
    {
    shmctl(shmid, IPC_RMID, 0);
    printf(Shared memory segment marked for deletionn);
    }
    changemode(int shmid, char mode)
    {
    struct shmid_ds myshmds;
    shmctl(shmid, IPC_STAT, &myshmds);
    printf(Old permissions were %on, myshmds.shm_perm.mode);
    sscanf(mode, %o, &myshmds.shm_perm.mode);
    shmctl(shmid, IPC_SET, &myshmds);
    printf(New permissions are  %on, myshmds.shm_perm.mode);
    }
# include <sys/types.h>
# include <sys/socket.h>
# include <linux/netlink.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define NETLINK_USER 31 
# define MAX_PAYLOAD 2048
int main()
{
struct sockaddr_nl source_nladdr, destination_nladdr;
struct nlmsghdr *nlh=NULL ;
struct iovec iov;
struct msghdr message ;
int s=socket(AF_NETLINK ,SOCK_RAW , NETLINK_USER );

//Defining Source Address  
memset(&source_nladdr, 0 ,sizeof(source_nladdr));
source_nladdr.nl_family= AF_NETLINK ;
source_nladdr.nl_pad=0;
source_nladdr.nl_pid = getpid();
bind(s, (struct sockaddr*)&source_nladdr, sizeof(source_nladdr));

//Defining Desitination Address
memset(&destination_nladdr, 0 ,sizeof(destination_nladdr));
destination_nladdr.nl_family= AF_NETLINK ;
destination_nladdr.nl_pad=0;
destination_nladdr.nl_pid = 0; /* destined to kernel */

//Create Message to be sent to Kernel
nlh = (struct nlmsghdr *)malloc(100);
memset(nlh , 0 , 100);
strcpy(NLMSG_DATA(nlh), "Knock Knock CMPE142!!!" );
nlh->nlmsg_len =100;
nlh->nlmsg_pid = getpid();
nlh->nlmsg_flags = 1;
nlh->nlmsg_type = 0;

/*iov structure */
iov.iov_base = (void *)nlh;
iov.iov_len = nlh->nlmsg_len;

/* Duplex communication of Message between User and Kernel */
memset(&message,0,sizeof(message));
message.msg_name = (void *) &destination_nladdr ;
message.msg_namelen=sizeof(destination_nladdr);
message.msg_iov = &iov;
message.msg_iovlen = 1;
//Send message and wait for Kernel to reply
sendmsg(s, &message, 0);
printf("Waiting for message from Kernel\n");
//Block on Receive till Kernel Sends reply
recvmsg(s,&message,0);
printf("Received Message: %s\n",NLMSG_DATA(nlh));
close(s);
return (EXIT_SUCCESS);
}

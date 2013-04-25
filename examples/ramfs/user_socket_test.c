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
struct sockaddr_nl s_nladdr, d_nladdr;
struct nlmsghdr *nlh=NULL ;
struct iovec iov;
struct msghdr message ;
int s=socket(AF_NETLINK ,SOCK_RAW , NETLINK_USER );

//Defining Source Address  
memset(&s_nladdr, 0 ,sizeof(s_nladdr));
s_nladdr.nl_family= AF_NETLINK ;
s_nladdr.nl_pad=0;
s_nladdr.nl_pid = getpid();
bind(s, (struct sockaddr*)&s_nladdr, sizeof(s_nladdr));

//Defining Desitination Address
memset(&d_nladdr, 0 ,sizeof(d_nladdr));
d_nladdr.nl_family= AF_NETLINK ;
d_nladdr.nl_pad=0;
d_nladdr.nl_pid = 0; /* destined to kernel */

//Fill the netlink message header
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
message.msg_name = (void *) &d_nladdr ;
message.msg_namelen=sizeof(d_nladdr);
message.msg_iov = &iov;
message.msg_iovlen = 1;
sendmsg(s, &message, 0);
printf("Waiting for message from Kernel\n");
recvmsg(s,&message,0);
printf("Received Message: %s\n",NLMSG_DATA(nlh));
close(s);
return (EXIT_SUCCESS);
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int fd, len, ret;
static char gpio_path[100];
static char file_path[100];

static int gpio_export(char *args)
{
		fd = open("/sys/class/gpio/export", O_WRONLY);
		if(fd < 0){
				printf("/sys/class/gpio/export no such of file \n");
				return -1;
		}

		len = strlen(args);
		ret = write(fd, args, len);
		if(fd < 0){
				printf("write file error %s \n", __FUNCTION__);
				close(fd);
				return -1;
		}
		close(fd);
		return 0;
}


static int gpio_unexport(char *args)
{
		fd = open("/sys/class/gpio/unexport", O_WRONLY);
		if(fd < 0){
				printf("/sys/class/gpio/export no such of file \n");
				return -1;
		}

		len = strlen(args);
		ret = write(fd, args, len);
		if(fd < 0){
				printf("write file error %s \n", __FUNCTION__);
				close(fd);
				return -1;
		}
		close(fd);
		return 0;
}

static int gpio_ctrl(char *argv, char *val)
{
		sprintf(file_path, "%s%s", gpio_path, argv);
		printf("%s  %s\n", file_path, val);
		fd = open(file_path, O_WRONLY);
		if(fd < 0){
				printf("%s no such of file \n", file_path);
				return -1;
		}

		len = strlen(val);
		ret = write(fd, val, len);
		if(fd < 0){
				printf("write file error %s \n", __FUNCTION__);
				close(fd);
				return -2;
		}
		close(fd);
		return 0;
}

int read_gpioValue(char *path)
{
		char val[100];
		sprintf(file_path, "%s%s", gpio_path, path);
		ret = open(file_path, O_RDONLY);
		if(ret < 0){
			printf("open %s file error\n", file_path);
			return -1;
		}

		ret = read(fd, val, strlen(val));
		if(!strcmp(val, "1")){
			printf("%s read value is 1\n", file_path);
			close(fd);
			return 0;
		}
		if(!strcmp(val, "0")){
			printf("%s read value is 0\n", file_path);
			close(fd);
			return 1;
		}
}

int main(int argc, char *argv[])
{
//		printf("The code is segement\n");
		sprintf(gpio_path, "/sys/class/gpio/gpio%s/", argv[1]);
		if(access(gpio_path, F_OK))
				gpio_export(argv[1]);

//		printf("control direction\n");
		/*gpio_ctrl("direction", "out");*/
		gpio_ctrl("direction", "in");
//		printf("control value\n");
		read_gpioValue("value");
/*		gpio_ctrl("value", argv[2]);*/

		gpio_unexport(argv[1]);
}


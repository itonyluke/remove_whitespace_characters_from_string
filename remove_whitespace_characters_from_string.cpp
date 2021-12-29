//
// Created by Waves Anisha on 12/27/21.
//

#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>

#define DARK_GREY "\033[90m"
#define GREY "\033[2m"
#define DEFAULT "\033[0m"
#define YELLOW "\033[33m"

#define DENOMINATOR 8

//structure to hold the terminal window size
typedef struct s_w
{
	unsigned short	ws_rows;
	unsigned short	ws_cols;
	unsigned short	ws_xpixel;
	unsigned short	ws_ypixel;
}				t_w;

//outputs the divider line that consists of '*' symbol for the length dependent on the DENOMINATOR
void output_divider_line(void)
{
	t_w w;
	int term_fd;

	term_fd = open("/dev/tty", O_RDONLY);
	if (term_fd == -1)
	{
		std::cout << "/dev/tty: fd == -1" << std::endl;
		exit(EXIT_FAILURE);
	}
	//Get terminal window size
	if (ioctl(term_fd, TIOCGWINSZ, &w) == -1)
		std::cout << "ioctl == -1" << std::endl;

	//	if you would like to see the amount of columns and rows uncomment the lines below
	//
	//	std::cout << GREY << "This terminal window is\n" << w.ws_rows << " rows by " << w.ws_cols << " columns" << DEFAULT << std::endl;
	//	std::cout << GREY << "(" << w.ws_xpixel << " by "<< w.ws_ypixel << " pixels)" << DEFAULT << std::endl;

	for (unsigned int i = 0; i < w.ws_cols / DENOMINATOR; i++)
		std::cout << DARK_GREY << "*";
	std::cout << std::endl;
	std::cout << DEFAULT;
	return;
}

//removes_white_space_characters_at_the_beginning_of_the_string
std::string remove_white_space_characters_at_the_beginning(std::string &str)
{
	unsigned int i, len;
	std::string str1;

	i = 0;
	while (std::isspace(str[i]))
		i++;
	len = str.length();
	str1 = str.substr(i, len - i);
	return (str1);
}

//removes_white_space_characters_at_the_end_of_the_string
std::string remove_white_space_characters_at_the_end(std::string &str)
{
	unsigned int i;
	std::string str1;

	i = str.length() - 1;
	while (std::isspace(str[i]))
		i--;
	str1 = str.substr(0, i + 1);
	return (str1);
}

//prompts_usage
void prompt_usage()
{
	output_divider_line();
	std::cout << YELLOW << "Usage:\n./a.out \"            string      with   white-space characters                     \""<< DEFAULT << std::endl;
	output_divider_line();
	exit(EXIT_FAILURE);
}

//removes_white_space_characters_in_the_middle_of_the_string
void remove_white_space_characters_in_the_middle(std::string &str)
{
	std::string character;

	character = ' ';
	unsigned int i = 0, j = 0;

	while (str[i] != '\0')
	{
		while (str[i] != '\0')
		{
			if (std::isspace(str[i]))
			{
				j = i;
				while (std::isspace(str[j]))
					j++;
				break;
			}
			i++;
		}
		str.erase(i, j - i);
//		comment the line below if you would like to remove all white-space characters
		str.insert(i, character);
		i++;
	}
}

//checks_string_if_it_is_empty_or_if_it_contains_only_white-space_characters
void check_str(std::string &str)
{
	if (str.empty())
		prompt_usage();
	else if (std::all_of(str.begin(), str.end(), isspace))
		prompt_usage();
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		output_divider_line();
		std::string str, str1, str2;

		str = argv[1];
		check_str(str);
//		commented lines below output intermediate results
//		std::cout << GREY << "initial string\t" << DEFAULT << str << std::endl;
		str1 = remove_white_space_characters_at_the_beginning(str);
//		std::cout << GREY << "removed white-space characters at the beginning\t" << DEFAULT << str1 << std::endl;
		str2 = remove_white_space_characters_at_the_end(str1);
//		std::cout << GREY << "removed white-space characters at the end\t" << DEFAULT << str2 << std::endl;
		remove_white_space_characters_in_the_middle(str2);
//		std::cout << GREY << "removed white-space characters in the middle\t" << DEFAULT << str2 << std::endl;
		std::cout << str2 << std::endl;
		output_divider_line();
	}
	else
		prompt_usage();
	return (0);
}

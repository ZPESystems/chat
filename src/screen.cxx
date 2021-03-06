#include "screen.h"
#include <iostream>

WINDOW *messages_window = NULL;
WINDOW *user_data_window = NULL;

WINDOW *create_win(int h, int w, int starty, int startx, int with_box)
{
	WINDOW *win;

	win = newwin(h, w, starty, startx);
	if (with_box)
		box(win, 0, 0);
	wrefresh(win);

	return win;
}

void add_message(std::string msg)
{
#ifdef ENABLE_NCURSES
	wprintw(messages_window, "%s\n", msg.c_str());
	wrefresh(messages_window);
#else
	std::cout << msg << std::endl;
#endif
}

void end_screen()
{
#ifdef ENABLE_NCURSES
	if (messages_window)
		delwin(messages_window);
	if (user_data_window)
		delwin(user_data_window);
	endwin();
#endif
}

void init_screen()
{
#ifdef ENABLE_NCURSES
	initscr();

	user_data_window = create_win(3, COLS, LINES - 3, 0, 1);
	messages_window = create_win(LINES - 3, COLS, 0, 0, 0);

	scrollok(messages_window, TRUE);
#endif
}

std::string get_user_input()
{
#ifdef ENABLE_NCURSES
	werase(user_data_window);
	box(user_data_window, 0, 0);
	wmove(user_data_window, 1, 1);
	wrefresh(user_data_window);

	std::vector<char> user_data;

	while (true) {
		int key = wgetch(user_data_window);

		if (key == '\n')
			break;

		user_data.push_back(static_cast<char>(key));
	}

	std::string retstr(user_data.begin(), user_data.end());

	return retstr;
#else
	std::string ret;
	std::cin >> ret;
	return ret;
#endif
}

/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "chat1002.h"

char username[MAX_INPUT] = "Me";

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chappie";

}

/*
 * Set username of the user.
 */

char* chatbot_set_username(char *name) {
	strcpy(username, name);
}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return username;

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	return compare_token(intent, "load") == 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
	int no_of_responses = 0;
	/* to be implemented */
	if (inv[1] == NULL) {
		strcpy(response, "No file is inputted");
	}
	else {
		FILE* file_ptr;

		if (file_ptr = fopen(inv[1], "r")) {
			no_of_responses = knowledge_read(file_ptr);
			fclose(file_ptr);
			snprintf(response, n, "Read %d responses from %s", no_of_responses, inv[1]);
		}
		else {
			snprintf(response, n , "\"%s\" file not found!", inv[1]);
		}
	}

	return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char* intent) {

	/* to be implemented */
	return compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "who") == 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.	
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
	snprintf(response, n, "Sorry I don't understand your question still. Not implemented");

	return 0;

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

	return compare_token(intent, "reset") == 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {

	knowledge_reset();
	snprintf(response, n, "Chatbot is now reset");

	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

	return compare_token(intent, "save") == 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
	snprintf(response, n, "Sorry I still can't save yet, not implemented.");

	return 0;

}


/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {
	char* smalltalk[] = { "hello", "yo", "hi", "oi", "hiya", "heyyo", "greetings", "hey", "wassup", "moshi", "ohaiyo", "konichiwa", "goodbye", "bye", "cya", "tell", "time", "date", "joke", "fact"};
	size_t smalltalk_length = sizeof(smalltalk) / sizeof(smalltalk[0]);
	for (int i = 0; i < smalltalk_length; i++) {
		if (compare_token(intent, smalltalk[i]) == 0)
			return 1;
	}
	return 0;

}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {
	if (compare_token(inv[0], "time") == 0 || compare_token(inv[0], "date") == 0) {
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		if (rawtime == -1) {
			snprintf(response, MAX_RESPONSE, "Something is has happened, could not get the time");
			return 0;
		}
		char* formatted_response[MAX_RESPONSE];
		sprintf(formatted_response, "It is now %02d:%02d:%02d on %02d/%2d/%4d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
		snprintf(response, MAX_RESPONSE, formatted_response);
		return 0;
	}
	if ((compare_token(inv[0], "tell") == 0 && compare_token(inv[1], "me") == 0) ||
		compare_token(inv[0], "joke") == 0 ||
		compare_token(inv[0], "fact") == 0) {
		int choice = 0;
		for (int i = 0; i < inc; i++) {
			if (compare_token(inv[i], "fact") == 0) {
				choice = 1;
				break;
			}
			else if (compare_token(inv[i], "joke") == 0) {
				choice = 2;
				break;
			} 
		}
		if (choice == 1) {
			char* smalltalk_fun_facts[] = { "The first person convicted of speeding was going eight mph.", "The world wastes about 1 billion metric tons of food each year. It is actually sad.", "The severed head of a sea slug can grow a whole new body", "Goosebumps are meant to ward off predators.", "The wood frog can hold its pee for up to eight months." };
			size_t smalltalk_fun_facts_length = sizeof(smalltalk_fun_facts) / sizeof(smalltalk_fun_facts[0]);
			int random_response = rand() % smalltalk_fun_facts_length;
			snprintf(response, MAX_RESPONSE, smalltalk_fun_facts[random_response]);
		}
		else if (choice == 2) {
			char* smalltalk_jokes[] = { "What do you call a bagel that can fly?", "What do you call a joke without a punchline?", "What do you call someone that saw an Iphone being stolen?"};
			char* smalltalk_answers[] = { "A plain bagel", "Silence", "An IWitness" };
			size_t smalltalk_jokes_length = sizeof(smalltalk_jokes) / sizeof(smalltalk_jokes[0]);
			int random_response = rand() % smalltalk_jokes_length;
			printf("%s: %s\n", chatbot_botname(), smalltalk_jokes[random_response]);
			delay(1);
			snprintf(response, MAX_RESPONSE, smalltalk_answers[random_response]);
		}
		else {
			snprintf(response, MAX_RESPONSE, "Sorry I am unable to understand, try saying \"tell me a joke\" or \"tell me a fun fact\"");
		}
		return 0;
	}

	char* smalltalk_farewells[] = { "goodbye", "bye", "cya" };
	size_t smalltalk_farewells_length = sizeof(smalltalk_farewells) / sizeof(smalltalk_farewells[0]);
	for (int i = 0; i < smalltalk_farewells_length; i++) {
		if (compare_token(inv[0], smalltalk_farewells[i]) == 0) {
			int random_response = rand() % smalltalk_farewells_length;
			snprintf(response, MAX_RESPONSE, smalltalk_farewells[random_response]);
			return 1;
		}
	}

	char* smalltalk_greetings[] = { "hello", "yo", "hi", "oi", "hiya", "heyyo", "greetings", "hey", "wassup", "moshi", "ohaiyo", "konichiwa" };
	size_t smalltalk_greetings_length = sizeof(smalltalk_greetings) / sizeof(smalltalk_greetings[0]);
	int random_response = rand() % smalltalk_greetings_length;
	snprintf(response, MAX_RESPONSE, smalltalk_greetings[random_response]);
	return 0;

}

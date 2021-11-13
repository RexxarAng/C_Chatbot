/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {

	/* to be implemented */
	if (compare_token(intent, "what") == 0) {
		node* what_iterator = what_head;

		while (what_iterator != NULL) {
			if (compare_token(what_iterator->entity, entity) == 0) {
				return KB_FOUND;
			}
			what_iterator = what_iterator->next;
		}

		return KB_NOTFOUND;
	}
	else if (compare_token(intent, "where") == 0) {
		node* where_iterator = where_head;
		// Find if entity already exists, and replace the response
		while (where_iterator != NULL) {
			if (compare_token(where_iterator->entity, entity) == 0) {
				strncpy(where_iterator->response, response, MAX_RESPONSE);
				return KB_FOUND;
			}
			where_iterator = where_iterator->next;
		}
		return KB_NOTFOUND;
	}
	else if (compare_token(intent, "who") == 0) {
		node* who_iterator = who_head;
		// Find if entity already exists, and replace the response
		while (who_iterator != NULL) {
			if (compare_token(who_iterator->entity, entity) == 0) {
				strncpy(who_iterator->response, response, MAX_RESPONSE);
				return KB_FOUND;
			}
			who_iterator = who_iterator->next;
		}
		return KB_NOTFOUND;
	}
	else {
		return KB_INVALID;
	}

}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {

	/* to be implemented */
	if (compare_token(intent, "what") == 0) {
		node* what_iterator = what_head;
		// Find if entity already exists, and replace the response
		while(what_iterator != NULL) {
			if (compare_token(what_iterator->entity, entity) == 0) {
				strncpy(what_iterator->response, response, MAX_RESPONSE);
				return KB_FOUND;
			}
			what_iterator = what_iterator->next;
		} 
		
		// Create new node and insert at the end of linked list
		node* new_node = malloc(sizeof(node));
		if (new_node == NULL) {
			return KB_NOMEM;
		}
		strncpy(new_node->entity, entity, MAX_ENTITY);
		strncpy(new_node->response, response, MAX_RESPONSE);
		new_node->next = NULL;
		// if linked list is empty, set it to the new node
		if (what_head == NULL)
			what_head = new_node;
		// else search for the last node and set the next to the new node created, add node to the end of the linked list
		else {
			node* last_node = what_head;
			while (last_node->next != NULL) {
				last_node = last_node->next;
			}
			last_node->next = new_node;
		}
		return KB_FOUND;
	}
	else if (compare_token(intent, "where") == 0) {
		node* where_iterator = where_head;
		// Find if entity already exists, and replace the response
		while (where_iterator != NULL) {
			if (compare_token(where_iterator->entity, entity) == 0) {
				strncpy(where_iterator->response, response, MAX_RESPONSE);
				return KB_FOUND;
			}
			where_iterator = where_iterator->next;
		}

		node* new_node = malloc(sizeof(node));
		if (new_node == NULL) {
			return KB_NOMEM;
		}
		strncpy(new_node->entity, entity, MAX_ENTITY);
		strncpy(new_node->response, response, MAX_RESPONSE);
		new_node->next = NULL;
		// if linked list is empty, set it to the new node
		if (where_head == NULL)
			where_head = new_node;
		// else search for the last node and set the next to the new node created, add node to the end of the linked list
		else {
			node* last_node = where_head;
			while (last_node->next != NULL) {
				last_node = last_node->next;
			}
			last_node->next = new_node;
		}
		return KB_FOUND;
	}
		
	else if (compare_token(intent, "who") == 0) {
		node* who_iterator = who_head;
		// Find if entity already exists, and replace the response
		while (who_iterator != NULL) {
			if (compare_token(who_iterator->entity, entity) == 0) {
				strncpy(who_iterator->response, response, MAX_RESPONSE);
				return KB_FOUND;
			}
			who_iterator = who_iterator->next;
		}

		node* new_node = malloc(sizeof(node));
		if (new_node == NULL) {
			return KB_NOMEM;
		}
		strncpy(new_node->entity, entity, MAX_ENTITY);
		strncpy(new_node->response, response, MAX_RESPONSE);
		new_node->next = NULL;
		// if linked list is empty, set it to the new node
		if (who_head == NULL)
			who_head = new_node;
		// else search for the last node and set the next to the new node created, add node to the end of the linked list
		else {
			node* last_node = who_head;
			while (last_node->next != NULL) {
				last_node = last_node->next;
			}
			last_node->next = new_node;
		}
		return KB_FOUND;
	}
	else
		return KB_INVALID;

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE* f) {

	int no_of_responses = 0;
	char line[MAX_ENTITY + MAX_RESPONSE];
	char intent[MAX_INTENT], entity[MAX_ENTITY], response[MAX_RESPONSE];
	char* split_text;

	while (fgets(line, sizeof(line), f)) {
		//printf(line);

		if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
			continue;
		}

		if (strstr(line, "[what]")) {
			strcpy(intent, "what");
			continue;
		}
		else if (strstr(line, "[where]")) {
			strcpy(intent, "where");
			continue;
		}
		else if (strstr(line, "[who]")) {
			strcpy(intent, "who");
			continue;
		}

		if (strchr(line, '=')) {
			printf("%s\n", line);
			split_text = strtok(line, "=");
			strcpy(entity, split_text);
			split_text = strtok(line, "=");
			strcpy(response, split_text);
			int result = knowledge_put(intent, entity, response);
			if (result == KB_FOUND) {
				no_of_responses++;
			}

		}

	}
	return no_of_responses;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {

	/* to be implemented */

}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

	/* to be implemented */

}

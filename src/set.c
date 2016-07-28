/*************************************************************************
	> File Name: set.c
	> Author: hyolin 
	> Created Time: Sun 18 Jan 2015 10:14:15 AM CST
 ************************************************************************/
#include "set.h"

/* set_init */
void set_init(Set *set, int (*compare)(const void *key1, const void *key2),
                void (*destroy)(void *data))
{
	list_init(set, compare, destroy);
	//set->compare = compare;

	return;
}

/* set_insert */
int set_insert(Set *set, const void *data)
{
	/* Don't allow insert the same member */
	if (set_is_member(set, data)) {
		return 1;
	}
	/* Insert the data return 0 if success else return -1 */
	return list_ins_next(set, NULL, data);
}

/* set_remove */
int set_remove(Set *set, void **data)
{
	ListNode *element, *prev = NULL;

	/* search the data in the set return -1 if data not found */
	if ((element = list_search(set, *data, prev)) == NULL)
		return -1;

	return list_rm_next(set, prev, data);
}

/* set_union */
int set_union(Set *setu, const Set *set1, const Set *set2)
{
	ListNode *element;
	void *data;

	set_init(setu, set1->compare, NULL);

	for (element = list_head(set1); element != NULL; element = list_next(element)) {
		if ((list_ins_next(setu, list_tail(set1), list_data(element))) != 0) {
			set_destroy(setu);
			return -1;
		}
	}
	/* insert the member of the set2 into set1 */
	for (element = list_head(set2); element != NULL; element = list_next(element)) {
		data = list_data(element);
		if (set_is_member(setu, data)) {
			continue;
		}

		data = list_data(element);
		if (list_ins_next(setu, list_tail(setu), data) != 0) {
			set_destroy(setu);
			return -1;
		}
	}

	return 0;
}

/* set_intersection */
int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
	ListNode *element;

	/* Initialize the seti */
	set_init(seti, set1->compare, NULL);

	/* Insert the element from both set1 and set2 */
	for (element = list_head(set1); element != NULL;element = list_next(element)) {
		if (!set_is_member(set2, list_data(element)))
			continue;

		if (list_ins_next(seti, list_tail(seti), element) != 0) {
			set_destroy(seti);
			return -1;
		}
	}
	return 0;
}

/* set_difference */
int set_difference(Set *setd, const Set *set1, const Set *set2)
{
	ListNode *element;
	/* Initialize the setd */
	set_init(setd, set1->compare, NULL);

	/* Insert the element from set1 not set2 */
	for (element = list_head(set1); element != NULL; element = list_next(element)) {
		if (set_is_member(set2, list_data(element)))
			continue;

		if (list_ins_next(setd, list_tail(setd), list_data(element)) != 0) {
			set_destroy(setd);
			return -1;
		}	
	}

	return 0;
}

/* set_is_member */
int set_is_member(const Set *set, const void *data)
{
	return (list_search(set, data, NULL) != NULL);
}

/* set_is_subset */
int set_is_subset(const Set *set1, const Set *set2)
{
	if (set_size(set1) > set_size(set2))
		return 0;
	ListNode *element;

	/* Test if set1 is a subset of set2 */
	for (element = list_head(set1); element != NULL; element = list_next(element)) {
		if (!set_is_member(set2, list_data(element)))
			return 0;
	}

	return 1;
}

/* set_is_equal */
int set_is_equal(const Set *set1, const Set *set2)
{
	if (set_size(set1) != set_size(set2))
		return 0;
	return set_is_subset(set1, set2);
}

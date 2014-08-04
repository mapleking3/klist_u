#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hlist.h"
#include "klist.h"

#define STU_HT_SIZE 4

struct stu_node {
    unsigned int        sn_no;
    char                stu_name[32];
    struct hlist_node   node;
};

static struct hlist_head stu_ht[STU_HT_SIZE];

struct stu {
	int num;
	char name[20];
	struct list_head list;
};

int test_list(void)
{
	struct stu *list_node = NULL;
	struct list_head *pos = NULL,*n = NULL;
	struct stu *pnode = NULL;


	struct stu *head = (struct stu *)malloc(sizeof(struct stu));
	if (head == NULL) {
		printf("file,%s line,%d:malloc error!\n",__FILE__,__LINE__);
		exit(1);
	}
	
	INIT_LIST_HEAD(&head->list);

	list_node = (struct stu *)malloc(sizeof(struct stu));
	if (list_node == NULL) {
		printf("file,%s line,%d:malloc error!\n",__FILE__,__LINE__);
		exit(1);
	}

	list_node->num = 0;
	strcpy(list_node->name,"xiaoming");
	list_add_tail(&list_node->list,&head->list);

	list_node = (struct stu *)malloc(sizeof(struct stu));
	if (list_node == NULL) {
		printf("file,%s line,%d:malloc error!\n",__FILE__,__LINE__);
		exit(1);
	}

	list_node->num = 1;
	strcpy(list_node->name,"xiaohua");
	list_add_tail(&list_node->list,&head->list);
	
	if (list_empty(&head->list)) {
		printf("list is empty!\n");
	} else {	
		list_for_each(pos,&head->list) {
			pnode = list_entry(pos,struct stu,list);
			printf("num:%d,name %s\n",pnode->num,pnode->name);	
		}
	}

	list_for_each_safe(pos,n,&head->list) {
		list_del(pos);
		pnode = list_entry(pos,struct stu,list);
		printf("num %d has removed from the list!\n",pnode->num);
	}	free(pnode);

	free(head);
	return 0;
}

int main(void)
{
    int i = 0;
    for (i = 0; i < STU_HT_SIZE; ++i)
    {
        INIT_HLIST_HEAD(&stu_ht[i]);
    }

    for (i = 0; i < 12; ++i)
    {
        struct stu_node *stu = (struct stu_node *)malloc(
                sizeof(struct stu_node));
        assert(NULL != stu);
        printf("Please input sn_no and name:\n");
        scanf("%d", &stu->sn_no);
        scanf("%s", stu->stu_name);
        INIT_HLIST_NODE(&stu->node);

        hlist_add_head(&stu->node, &stu_ht[stu->sn_no%STU_HT_SIZE]);
    }

    for (i = 0; i < STU_HT_SIZE; ++i)
    {
        printf("\nIn %d Hash List:\n", i);
        struct hlist_node *pos = NULL;
        hlist_for_each(pos, &stu_ht[i])
        {
            struct stu_node *stu = hlist_entry(pos, struct stu_node, node);
            printf("no:%d name:%s\n", stu->sn_no, stu->stu_name);
        }
    }
    return 0;
}

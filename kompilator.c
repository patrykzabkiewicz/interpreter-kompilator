#include <stdio.h>
#include <stdlib.h>
#include "includes.h"
#include "y.tab.h"



static int      etk;

int
ex(nodeType * p)
{
	int             etk1, etk2;


	if (!p)
		return 1;

	switch (p->type) {
	case typeCon:
		printf("\tpush\t%d\n", p->value.con.value);
		break;

	case typeId:
		printf("\tpush\t%c\n", p->value.id.i + 'a');
		break;

	case typeOpr:
		switch (p->value.opr.oper) {
		case WHILE:
			printf("ETK%02d:\n", etk1 = etk++);
			ex(p->value.opr.op[0]);
			printf("\tjz\tETK%02d\n", etk2 = etk++);
			ex(p->value.opr.op[1]);
			printf("\tjmp\tETK%02d\n", etk1);
			printf("ETK%02d:\n", etk2);
			break;
		case IF:
			ex(p->value.opr.op[0]);
			if (p->value.opr.nops > 2) {
				/* if else */
				printf("\tjz\tETK%02d\n", etk1 = etk++);
				ex(p->value.opr.op[1]);
				printf("\tjmp\tETK%02d\n", etk2 = etk++);
				printf("ETK%02d:\n", etk1);
				ex(p->value.opr.op[2]);
				printf("ETK%02d:\n", etk2);
			} else {
				/* if */
				printf("\tjz\tETK%02d\n", etk1 = etk++);
				ex(p->value.opr.op[1]);
				printf("ETK%02d:\n", etk1);
			}
			break;
		case PRINT:
			ex(p->value.opr.op[0]);
			printf("\tprint\n");
			break;
		case '=':
			ex(p->value.opr.op[1]);
			printf("\tpop\t%c\n", p->value.opr.op[0]->value.id.i + 'a');
			break;
		case POSTINC:
			ex(p->value.opr.op[0]);
			printf("\tpush\t1\n");
			printf("\tadd\n");
			break;
		case POSTDEC:
			ex(p->value.opr.op[0]);
			printf("\tpush\t1\n");
			printf("\tsub\n");
			break;
		case PREINC:
			ex(p->value.opr.op[0]);
			printf("\tpush\t1\n");
			printf("\tadd\n");
			break;
		case PREDEC:
			ex(p->value.opr.op[0]);
			printf("\tpush\t1\n");
			printf("\tsub\n");
			break;
		case ASPLUS:
			ex(p->value.opr.op[0]);
			ex(p->value.opr.op[1]);
				printf("\tadd\n");
			break;
		case ASMINUS:
			ex(p->value.opr.op[0]);
			ex(p->value.opr.op[1]);
				printf("\tsub\n");
			break;
		case ASMULTI:
			ex(p->value.opr.op[0]);
			ex(p->value.opr.op[1]);
				printf("\tmul\n");
			break;
		case ASDEVIDE:
			ex(p->value.opr.op[0]);
			ex(p->value.opr.op[1]);
				printf("\tdiv\n");
			break;

		case FACTORIAL:
			ex(p->value.opr.op[0]);
			printf("\tfac\n");
			break;
		case UMINUS:
			ex(p->value.opr.op[0]);
			printf("\tneg\n");
			break;
		default:
			ex(p->value.opr.op[0]);
			ex(p->value.opr.op[1]);
			switch (p->value.opr.oper) {
			case '+':
				printf("\tadd\n");
				break;

			case '-':
				printf("\tsub\n");
				break;

			case '*':
				printf("\tmul\n");
				break;

			case '^':
				printf("\tpow\n");
				break;

			case '/':
				printf("\tdiv\n");
				break;

			case '<':
				printf("\tcompLT\n");
				break;

			case '>':
				printf("\tcompGT\n");
				break;

			case GE:
				printf("\tcompGE\n");
				break;

			case LE:
				printf("\tcompLE\n");
				break;

			case NE:
				printf("\tcompNE\n");
				break;

			case EQ:
				printf("\tcompEQ\n");
				break;
			}
		}
	}


	return 0;
}

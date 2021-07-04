#include "treePublic.h"
//#include "treeAddition.h"

#define OK 1
#define KO 0

int
main (
  void
   )
{
  node_t *root, *tmp;
  data_t d;
  int retValue, end = 0;
  char row[MAXC];
  FILE *fp = NULL;\
  int *array,h;
  int np=0,length=0;
  int key1,key2,res;

  root = NULL;
  root = createEmptyTree();

  while (!end) {

    fprintf (stdout, "User selection\n");
    fprintf (stdout, "\t1) Insert one single node\n\t2) Cancel one single node\n\t3) Search a node\n");
    fprintf (stdout, "\t4) Print BST on stdout\n\t5) Write BST on file\n\t6) Read BST from file\n");
    fprintf (stdout, "\t7) Compute min and max\n");
    fprintf(stdout, "\t8) Count nodes with 0,1,2 children\n \t9) Count number of nodes at each level");
    fprintf(stdout, "\t10) number of paths ending in a leaf and number of edges. \n");
    fprintf(stdout, "\t11) distance between two nodes.\n \t12) End\n");
    scanf ("%1s", row);

    switch (atoi(row)) {

      case 1:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	root = insert (root, d);
	break;

      case 2:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	root = delete (root, d);
	break;

      case 3:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }

	tmp = searchI (root, d);
	if (tmp != NULL) {
	  fprintf (stdout, "Iterative Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Iterative Search: Not Found\n");
        }
	tmp = searchR (root, d);
	if (tmp  != NULL) {
	  fprintf (stdout, "Recursive Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Recursive Search: Not Found\n");
        }
	break;

      case 4:
	writeTree (stdout, root, INORDER);
	break;

      case 5:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

        if (strcmp (row, "stdout") == 0) {
          fp = stdout;
        } else {
   	  fp = fopen (row, "w");
        }

        if (fp == NULL) {
         fprintf (stderr, "Error Opening File %s\n", row);
         break;
	}

	writeTree (fp, root, PREORDER);

        if (strcmp (row, "stdout") != 0) {
	  fclose(fp);
	}
	break;

      case 6:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

	fp = fopen (row, "r");
	if (fp == NULL) {
	  fprintf (stderr, "Error Opening File %s\n", row);
	} else {
	  freeTree (root);
	  root = readTree (fp);
	}
	break;

      case 7:
        fprintf (stdout, "Tree minimum iterative: ");
        tmp = treeMinI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree minimum recursive: ");
        tmp = treeMinR (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum iterative: ");
        tmp = treeMaxI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum recursive: ");
        tmp = treeMaxR (root);
        writeData (stdout, getData(tmp));
	break;

      case 8:
        array = malloc(3*sizeof(int));
        for (int i=0;i<3;i++){
            array[i] = 0;
        }
        countNode(root,array);
        for(int i=0;i<3;i++){
            fprintf(stdout,"Number of nodes with %d children: %d\n",i,array[i]);
        }
    break;
      case 9:
        h = height(root);
        array = malloc(h*sizeof(int));
        for (int i=0;i<h;i++){
            array[i] = 0;
        }
        countNode(root,array);
        for(int i=0;i<h;i++){
            fprintf(stdout,"Number of nodes at level %d : %d\n",i,array[i]);
        }
    break;
      case 10:

        countPath(root,&np,&length);
        fprintf(stdout,"Number of paths to a leaf: %d\n number of edges:%d",np,length);
    break;
      case 11:

        fprintf(stdout,"Enter key1:\n");
        scanf("%d",&key1);
        fprintf(stdout,"Enter key2:\n");
        scanf("%d",&key2);
        res = visit(root,key1,key2);
        return res;
    break;
      case 12:
	end = 1;
	break;

      default:
	fprintf (stderr, "Unknown Option.\n");
	break;
    }
  }

  freeTree(root);

  return (OK);
}




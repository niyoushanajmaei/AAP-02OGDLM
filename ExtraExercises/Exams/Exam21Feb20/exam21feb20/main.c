#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51

/*
    choose from the available items
    check if weight is below W
    chose solution with max price in the terminating condition
*/

typedef struct item_s{
    char *name;
    int weight,price,count;
}item;

typedef struct list_s{
    item *items;
    int weight,price,count;
}list;

list read_file(FILE *f,int n);
list find_sol(list store, int n, int w);
void find_sol_r(list store, list cart,list curr, int n, int w,int *max_price_ptr);
void copy_list(list src, list dst, int n);
void write_sol(list cart, int n);
void add_to_cart(list store,list cart, int i);
void remove_from_cart(list store, list cart, int i);

int main(int argc, char *argv[])
{
    list store, cart;
    int n,w;
    FILE *f;
    if (argc!=3){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }

    f = fopen(argv[1],"r");
    fscanf(f,"%d",&n);
    sscanf(argv[2],"%d",&w);

    store = read_file(f,n);
    cart = find_sol(store,n,w);
    write_sol(cart,n);

    fclose(f);
    free(store.items);
    free(cart.items);
    return 0;
}


list read_file(FILE *f,int n){
    list store;
    item *items = malloc(n*sizeof(item));
    char tmp[MAX];
    if (items==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    store.items = items;
    for (int i=0;i<n;i++){
        fscanf(f,"%s %d %d %d",tmp, &store.items[i].count, &store.items[i].weight, &store.items[i].price);
        store.items[i].name = strdup(tmp);
    }
    return store;
}

list find_sol(list store, int n, int w){
    int price = 0;
    list cart;
    item *items = malloc(n*sizeof(item));
    if (items==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    cart.items = items;
    cart.count = 0;
    cart.weight= 0;
    cart.price = 0;
    for (int i=0;i<n;i++){
        cart.items[i].name = strdup(store.items[i].name);
        cart.items[i].count = 0;
        cart.items[i].weight = 0;
        cart.items[i].price = 0;
    }
    find_sol_r(store,cart,cart,n,w,&price);
   return cart;
}

void find_sol_r(list store, list cart, list curr, int n, int w,int *max_price_ptr){
    int i;
    if (cart.price>*max_price_ptr){
        *max_price_ptr = cart.price;
        copy_list(curr, cart,n);
    }
    for (i=0;i<n;i++){
        if (store.items[i].count>0){
            add_to_cart(store,curr,i);
            if (curr.weight <w){
                find_sol_r(store,cart,curr,n,w,max_price_ptr);
            }
            remove_from_cart(store,curr,i);
        }
    }
    return;
}

void copy_list(list src, list dst, int n){
    for (int i=0;i<n;i++){
        dst.items[i].count = src.items[i].count;
        dst.items[i].weight = src.items[i].weight;
        dst.items[i].price = src.items[i].price;
        strcpy(dst.items[i].name, src.items[i].name);
    }
    dst.count = src.count;
    dst.weight = src.weight;
    dst.price = src.price;
    return;
}

void write_sol(list cart, int n){
    if (cart.price != 0){
        for (int i=0;i<n;i++){
            fprintf(stdout,"%s %d %d %d\n",cart.items[i].name, cart.items[i].count, cart.items[i].weight, cart.items[i].price);
        }
        fprintf(stdout,"\nsolution %d %d %d",cart.count,cart.weight,cart.price);
    }else{
        fprintf(stdout,"No solution found.\n");
    }
    return;
}

void add_to_cart(list store, list cart, int i){
    cart.items[i].count++;
    store.items[i].count --;
    cart.items[i].price += store.items[i].price;
    cart.items[i].weight += store.items[i].weight;
    cart.price += store.items[i].price;
    cart.count ++;
    cart.weight += store.items[i].weight;
    return;
}

void remove_from_cart(list store, list cart, int i){
    cart.items[i].count--;
    store.items[i].count ++;
    cart.items[i].price -= store.items[i].price;
    cart.items[i].weight -= store.items[i].weight;
    cart.price -= store.items[i].price;
    cart.count --;
    cart.weight -= store.items[i].weight;
    return;
}

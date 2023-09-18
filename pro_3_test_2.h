#ifndef hw_3_test_2 
#define hw_3_test_2

#define LENGTH_OF_CHAR 32
#define LOGFILE "Log.txt"

typedef struct {
    int Movie_code;
    char *Mfname;
    char *Mlname;
    int year;
    int length_of_movie;
    char *director_Fname;
    char *director_Lname;
} M_DATA;

typedef struct {
    int Ratings_id;
    int Movie_code;
    char *Rname;
    char *status;
    int rating_value;
    //int found;
    //float avgrating;
} R_DATA;

typedef struct r_nodeTag {
    R_DATA rating;
    struct r_nodeTag *next;
    struct r_nodeTag *previous;
    int index;
} R_NODE;

typedef struct nodeTag {
    M_DATA movie;
    struct r_nodeTag *rating;
    struct nodeTag *next;
    struct nodeTag *previous;
    int index;
} NODE;


NODE *buildList(NODE *pList);

R_NODE *buildR_List(R_NODE *rList);

NODE *getM_Data(FILE *pM_Data, M_DATA movie);

R_NODE *getR_Data(FILE *pR_Data, R_DATA rating);

NODE *makeNode(M_DATA line);

R_NODE *makeR_Node(R_DATA line);

NODE *append(NODE *head, M_DATA line);

void appendR_Data(R_NODE *head, R_DATA line);

NODE *prepend(NODE *head, M_DATA line);

R_NODE *prependR_Data(R_NODE *head, R_DATA line);

void printListAsc(NODE *pList);

void printListDesc(NODE *pList);

void printR_ListAsc(R_NODE *rList);

void printM_ListAsc(NODE *pList);

R_NODE *appendSingleR_Data(R_NODE *head, R_DATA line);

R_NODE *sortR_Node(R_NODE *head, R_NODE *tail);

R_NODE *changeR_Head(R_NODE *head, R_NODE *nextHead);

NODE *changeM_Head(NODE *head, NODE *nextHead);

NODE *addRatingsToMovies(NODE *movies, R_NODE *ratings);

void constructMainList(NODE *fullMovies, R_NODE *fullRatings);

bool searchByMovie_Code(NODE *pList, int movie_code);

bool searchByRating_Id(R_NODE *pList, int rating_id);

int checkUserChoice(char *answer);

void addNewRating(R_NODE *pList, int movie_code);

void addNewMovie(NODE *pList, int movie_code);

M_DATA allocM_Data(char *Mfname, char *Mlname, char *director_Fname, char *director_Lname, M_DATA movie);

R_DATA allocR_Data(char *Rname, char *status, R_DATA rating);

void deleteSingleRating(R_NODE *pList, int rating_id, int movie_code);

bool checkForRatings(R_NODE *rTag, int code);

NODE *deleteSingleMovie(NODE *pList, R_NODE *rList, int movie_code);

R_NODE *deleteInBulk(R_NODE *rList, int movie_code);

void writeChangesToFile(NODE *pTag, R_NODE *rTag);

void printMoviesToFile(NODE *pList, FILE *pM_Data);

void printRatingsToFile(R_NODE *pList, FILE *pR_Data);

R_NODE *editRating(R_NODE *pList, int movie_code);

NODE *editMovie(NODE *pList, int movie_code);

M_DATA getMovieData(int movie_code);

R_DATA getRatingById(R_NODE *pList, int rating_id);

M_DATA getMovieByMovie_Code(NODE *pList, int movie_code);

void resetIndexes(R_NODE *rList);

void resetMovieIndexes(NODE *pList);

void showUpdatedR_List(R_NODE *ratingList);

void showUpdatedList(NODE *movieList);

NODE *getratingsUnderAMovie(NODE *fullMovies, R_NODE *fullRatings, int movie_code) ;

void showMovie(NODE *movie, int movie_code);

void Searchfunction(NODE *movie );

void freeMovieList(NODE *fullmovie);

void freeRatingList(R_NODE *fullRatings);

#endif

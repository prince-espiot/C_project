#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "hw_3_test_2.h"


int main(void) {
    NODE *pList = NULL;
    R_NODE *rList = NULL;
    NODE *movieList = NULL;
    R_NODE *ratingList = NULL;
    FILE *log;
    int input=0, rating_id=0, movie_code=0, isYes=0;
    bool isExists=false, isRatingExists =false, isMovieExists=false, hasRatings=false;
    char answer[LENGTH_OF_CHAR];
    time_t currentTime = time(0);
    
    

    log = fopen(LOGFILE, "a+");
    if (log == NULL) {
        printf("Unable to open the file\n");
        exit(1300);
    }

    pList = buildList(pList);
    rList = buildR_List(rList);
    
    movieList = buildList (movieList);
    ratingList= buildR_List (ratingList);
    
    R_DATA ratingFromFile;
    M_DATA movieFromFile;

    while (rList->previous != NULL) {
        rList = rList->previous;
    }//go to head of ratings list
    while (pList->previous != NULL) {
        pList = pList->previous;
    }//go to head of movies list

	 constructMainList(pList, rList);

    do {
    	printf("----------------------------------------------------------------------------------------------------\n");
        printf("Please Enter and Option to execute: 1 , 2 , 3 , 4 , 5 or 0 \n");
        printf("Press '1' to see all entries\n");
        printf("Press '2' to edit entries\n");
        printf("Press '3' to search through entries\n");
        printf("Press '4' to delete an entry\n");
        printf("Press '5' to add an entry\n");
        printf("And press '0' to check-out\n\n**\tPlease Note: All other entries won't be recognized!'\t**\n\n");
        printf("-----------------------------------------------------------------------------------------------------\n");

        scanf("%d", &input);
        fprintf(log, "%d\n", input);
        fprintf(log, "visited main menu at %s\n", ctime(&currentTime));
        switch (input) {
            case 1://prints all items
            fprintf(log, "All items viewed\n");
            int displayInput = 0;
                do {
                    printf("Press '1' to print Ratings list\n");
                    printf("Press '2' to print Movies list\n");
                    printf("Press '3' to print Combined list\n");
                    printf("And press '0' to go back\n**\t"
                           "Please Note: All other entries won't be recognized!'\t**\n");
                    scanf("%d", &displayInput);
                    fprintf(log, "%d\n", displayInput);
                    fprintf(log, "%s", ctime(&currentTime));
                    switch (displayInput) {
                        case 1://show ratings list
                            printR_ListAsc(ratingList);
                            fprintf(log, "viewed rating list at %s\n", ctime(&currentTime));
                            break;
                        case 2://show Movies list
                           	printM_ListAsc(movieList);//REMOVE
                            fprintf(log, "viewed Movie list at %s\n", ctime(&currentTime));
                            break;
                        case 3://show joined list
                           	printListAsc(pList); 
                            fprintf(log, "viewed joined list at %s\n", ctime(&currentTime));
                            break;
                        default:
                            printf("Please try again!!\n");
                            fprintf(log, "Invalid entry\n");
                    }
                } while (displayInput != 0);
                break;//good
               
            case 2://edits available items
                fprintf(log, "user chose to edit entries\n");
                int editInput;
                do {
                    printf("Press '1' to edit one rating\n");
                    printf("Press '2' to edit one movie\n");
                    printf("And press '0' to go back\n\n**\t"
                           "Please Note: All other entries won't be recognized!'\t**\n\n");
                    scanf("%d", &editInput);
                    fprintf(log, "%d\n", input);
                    switch (editInput) {
                        case 1:
                            fprintf(log, "user chose to edit a rating\n");
                            printf("Please enter a movie_code:\n");
                            scanf("%d", &movie_code);
                            isMovieExists = searchByMovie_Code(movieList, movie_code);
                            if (!isMovieExists) {
                                printf("This movie_code doesn't exist, please try another movie_code\n");
                                break;
                            }
                            
                          // NODE *movie = getratingsUnderAMovie(movieList,ratingList,movie_code); removie fucntion
                        
							showMovie(pList,movie_code);
							
							
                            ratingList = editRating(rList, movie_code);
                            showUpdatedR_List(rList);
                            break;
                        case 2:
                            fprintf(log, "user chose to edit a movie\n");
                            printf("Please enter a movie_code:\n");
                            scanf("%d", &movie_code);
                            isMovieExists = searchByMovie_Code(movieList, movie_code);
                            if (!isMovieExists) {
                                printf("This movie_code doesn't exist, please try another movie_code\n");
                                break;
                            }
                            
                            M_DATA movieData = getMovieByMovie_Code(movieList, movie_code);

                            printf("Is this the movie you wish to edit?[Y/N]\n");
                            printf("%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", movieData.Movie_code, movieData.Mfname,
                                   movieData.Mlname, movieData.year, movieData.length_of_movie,
                                   movieData.director_Fname,
                                   movieData.director_Lname);
                            scanf("%s", answer);
                             isYes = checkUserChoice(answer);
                                if (!isYes) {
                                    printf("This movies stays, please try another movie_code.\n");
                                    break;
                                }
                            movieList = editMovie(movieList, movie_code);
                            showUpdatedList(movieList);
                            break;
                        
                        default:
                            printf("Please try again!!\n");
                            fprintf(log, "Invalid entry\n");
                    }
                } while (editInput!=0);
                break; //better

            case 3://search by movies_code
                fprintf(log, "Search through inventory\n");
              	 movieList = buildList(movieList);
                Searchfunction(movieList);
                break; //better
            case 4://delete an entry //GOOD
                fprintf(log, "user chose to delete an item\n");
                int deleteInput;
                do {
                    printf("Press '1' to remove a rating\n");
                    printf("Press '2' to remove a movie\n");
                    printf("And press '0' to check-out\n**\t"
                           "Please Note: All other entries won't be recognized!'\t**\n");
                    scanf("%d", &deleteInput);
                    fprintf(log, "%d\n", input);
                    switch (deleteInput) {
                        case 1://remove one rating
                            fprintf(log, "user chose to delete one rating\n");

                            do {
                                printf("Please enter a movie_code:\n");
                                scanf("%d", &movie_code);
                                isMovieExists = searchByMovie_Code(movieList, movie_code);
                                if (!isMovieExists) {
                                    printf("This movie_code doesn't exist, please try another movie_code\n");
                                }
                            } while (!isMovieExists);
								showMovie(movieList,movie_code);
                            do {
                                printf("Please enter a rating_id:\n");
                                scanf("%d", &rating_id);
                                 ratingFromFile = getRatingById(ratingList, rating_id);
                                  isRatingExists = movie_code == ratingFromFile.Movie_code;
                                if (!isRatingExists) {
                                    printf("This rating_id doesn't exist, please try another movie_code\n");
                                }
                            } while (!isRatingExists);

                            R_DATA ratingData = getRatingById(ratingList, rating_id);

                            printf("Is this the rating you wish to delete?[Y/N]\n");
                            printf("%3d %3d %-8s %-10s   %d\n", ratingData.Ratings_id, ratingData.Movie_code,
                                   ratingData.Rname, ratingData.status, ratingData.rating_value);
                            scanf("%s", answer);
                            isYes = checkUserChoice(answer);

                            if (isYes > 0) {
                                deleteSingleRating(ratingList, rating_id, movie_code);
                                
                            }
                            if (isYes < 0) {
                                printf("Invalid entry, please try again!!\n");
                                fprintf(log, "attempted rating delete at %s\n", ctime(&currentTime));
                                break;
                            }
                            if (isYes == 0) {
                                printf("Rating sheet remains unchanged!!\n");
                                fprintf(log, "discarded rating delete action at %s\n", ctime(&currentTime));
                                break;
                            }
                            showUpdatedR_List(ratingList);
                            fprintf(log, "rating list updated at %s\n", ctime(&currentTime));
                            break;
                        case 2://remove one movie; movies that still has ratings cannot be deleted;
                            fprintf(log, "user chose to delete a movie\n");
                            printM_ListAsc(movieList);//REMOVE
                            
                            printf("Please enter a movie_code:\n");
                            scanf("%d", &movie_code);
                            
                            isMovieExists = searchByMovie_Code(movieList, movie_code);
                            if (!isMovieExists) {
                                printf("This movie_code doesn't exist, please try another movie_code\n");
                                break;
                            }
                            M_DATA movieData = getMovieByMovie_Code(movieList, movie_code);

                            printf("Is this the movie you wish to delete?[Y/N]\n");
                            printf("%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", movieData.Movie_code, movieData.Mfname,
                                   movieData.Mlname, movieData.year, movieData.length_of_movie,
                                   movieData.director_Fname,
                                   movieData.director_Lname);
                            scanf("%s", answer);
                             isYes = checkUserChoice(answer);
                             if (isYes == 0) {
                                printf("This Movie stays, please try another Movie Code.\n");
                                fprintf(log, "attempted Movie delete action at %s\n", ctime(&currentTime));
                                break;
                            }
                            if (isYes < 0) {
                                printf("Invalid entry, please try again!!\n");
                                fprintf(log, "discarded Movie delete action at %s\n", ctime(&currentTime));
                                break;
                            }
                                

                            hasRatings = checkForRatings(ratingList, movie_code);
                            
                            if (hasRatings) {
                                printf("This movie still has ratings as seen below: \n");
                                showMovie(movieList,movie_code);
                                 printf("Do you wish to delete all the ratings of this movie as well?[Y/N]\n");
                                scanf("%s", answer);
                                isYes = checkUserChoice(answer);
                                if (isYes==0) {
                                    printf("This movies stays, please try another movie_code.\n");
                                    fprintf(log, "attempted Movie and rating delete action at %s\n",ctime(&currentTime));
                                    break;
                                }
                                if (isYes < 0) {
                                    printf("Invalid entry, please try again!!\n");
                                    fprintf(log, "discarded Movie and rating delete action at %s\n",
                                            ctime(&currentTime));
                                    break;
                                }
                                movieList = deleteSingleMovie(movieList, ratingList, movie_code);
                                showUpdatedList(movieList);
                                fprintf(log, "Movie and rating delete action at %s\n", ctime(&currentTime));
                                break;
                            } else {
                                pList = deleteSingleMovie(movieList, ratingList, movie_code);
                                showUpdatedList(movieList);
                                fprintf(log, "Movie and rating delete action at %s\n", ctime(&currentTime));
                                break;
                            }
                        
                        default:
                            printf("Please try again!! Wrong Entry!!\n");
                            fprintf(log, "Invalid entry\n");
                    }
                } while (deleteInput != 0);
                break; //better

            case 5://add an entry
                fprintf(log, "user chose to add an item\n");
                //user cannot add rating to a movies moves movie_code doesn't already exist
                //unless they are ready to add a new movie that corresponds to the new rating
                printf("Do you wish to add a movie to our list?[Y/N]\n");
                scanf("%s", answer);
                isYes = checkUserChoice(answer);
                if (isYes < 0) {
                    printf("invalid entry, please try again!!\n");
                    fprintf(log, "attempted Movie add action at %s\n", ctime(&currentTime));
                    break;
                }
                if (isYes>0) {
                    printf("Please enter a new movie_code:\n");
                    scanf("%d", &movie_code);
                    isExists = searchByMovie_Code(movieList, movie_code);
                    if (isExists == true) {
                        //if movie_code already exists then no need to duplicate it
                        //only possibility is to add new rating
                        printf("This movie_code already exists\n");
                        printf("Did you mean to add a rating with this movie_code?[Y/N]\n");
                        scanf("%s", answer);
                        isYes = checkUserChoice(answer);
                        if (isYes < 0) {
                            printf("invalid entry please try again!!\n");
                        }
                        if (isYes>0) {
                            addNewRating(ratingList, movie_code);
                            fprintf(log, "rating add action at %s\n", ctime(&currentTime));
                        showUpdatedR_List(ratingList);
                        }else {
						    printf("This movie_code already exists, please try another movie_code\n");
						}
                        break;
                    }else {
                    	addNewMovie(movieList, movie_code);
                    	fprintf(log, "Movie add action at %s\n", ctime(&currentTime));
					}
                    break;
                    
                  	 showUpdatedList(movieList);
                   break;
                } else{
                	do{
                		printf("Please enter the Movie code for this new rating:\n");
                        scanf("%d", &movie_code);
                        isExists = searchByMovie_Code(movieList, movie_code);
                        if (!isExists) { printf("This Movie code doesn't exist, please try another one\n"); }

					}while (!isExists);
					addNewRating(ratingList, movie_code);
					fprintf(log, "rating add action at %s\n", ctime(&currentTime));
				}

                break;
            case 0:
                writeChangesToFile(pList, rList);
                freeMovieList(pList);
                freeRatingList(rList);
                freeMovieList(movieList);
                freeRatingList(ratingList); 
                fclose(log);
            return 0;
            default:
                printf("Please try again!!\n");
                fprintf(log, "Invalid entry\n");
        }

    } while (input);
	//	better
}

void showUpdatedList(NODE *movieList) {
    printf("This movie has successfully been deleted.\n");
    printf("Here's your updated movie list.\n");
    printM_ListAsc(movieList);
    printf("All changes will be commited to file as soon as you exit the program.\n");
}

void showUpdatedR_List(R_NODE *ratingList) {
    printf("Here's your updated rating list.\n");
    printR_ListAsc(ratingList);
    printf("All changes will be commited to file as soon as you exit the program.\n");
}

void writeChangesToFile(NODE *pTag, R_NODE *rTag) {
    FILE *pM_Data, *pR_Data;

    pM_Data = fopen("Movies.txt", "w+");
    if (pM_Data == NULL) {
        printf("Error opening Movies file.\n");
        exit(2);
    }

    pR_Data = fopen("Ratings.txt", "w+");
    if (pR_Data == NULL) {
        printf("Error opening Ratings file.\n");
        exit(3);
    }

    if (pTag) { printMoviesToFile(pTag, pM_Data); }
    if (rTag) { printRatingsToFile(rTag, pR_Data); }

    fclose(pR_Data);
    fclose(pM_Data);
}


void showMovie(NODE *movie, int movie_code) {
	while (movie != NULL){
		if (movie_code == movie->movie.Movie_code) {
            printf("%d\t%s\t%s\t%d\t%s\t%s\n", movie->movie.Movie_code,
                   movie->movie.Mfname, movie->movie.Mlname, movie->movie.length_of_movie,
                   movie->movie.director_Fname, movie->movie.director_Lname);
            if (movie->rating != NULL) {
                printR_ListAsc(movie->rating);
            }
        
    }
    movie = movie->next;
	}
    

}

bool checkForRatings(R_NODE *rTag, int code) {
    if (rTag != NULL) {
        if (code == rTag->rating.Movie_code) {
            return true;
        }
        return checkForRatings(rTag->next, code);
    }
    return false;
}

void deleteSingleRating(R_NODE *pList, int rating_id, int movie_code) {

    if (pList == NULL) {
        printf("There's nothing to delete.\n");
        return;
    }
    R_NODE *tmp = NULL;
    bool isDeleted = false;

    if (movie_code == pList->rating.Movie_code && rating_id == pList->rating.Ratings_id) {

        if (pList->previous == NULL) {
            tmp = pList;
            pList = pList->next;
            pList->previous = NULL;
            free(tmp);
            resetIndexes(pList);
            isDeleted = true;
        } else if (pList->next == NULL) {
            tmp = pList;
            pList = pList->previous;
            pList->next = NULL;
            free(tmp);
            isDeleted = true;
        } else {
            tmp = pList;
            tmp->previous->next = tmp->next;
            tmp->next->previous = tmp->previous;
            free(tmp);
            resetIndexes(pList);
            isDeleted = true;
        }
    } else {
        deleteSingleRating(pList->next, rating_id, movie_code);
    }

    if (isDeleted) {
        printf("This rating has successfully been deleted.\n");
    }
}

void resetIndexes(R_NODE *rList) {
    if (rList != NULL) {
        rList->index = rList->index - 1;
        resetIndexes(rList->next);
    }//reset node indexes
}

void resetMovieIndexes(NODE *pList) {
    if (pList != NULL) {
        pList->index = pList->index - 1;
        resetMovieIndexes(pList->next);
    }//reset node indexes
}

R_NODE *deleteInBulk(R_NODE *rList, int movie_code) {

    R_NODE *tmp = NULL;
    if (rList == NULL) {
        return rList;
    }

    if (movie_code == rList->rating.Movie_code) {
        if (rList->previous == NULL) {
            tmp = rList;
            rList = rList->next;
            rList->previous = NULL;
            free(tmp);
            resetIndexes(rList);
        } else if (rList->next == NULL) {
            tmp = rList;
            rList = rList->previous;
            rList->next = NULL;
            free(tmp);
            return rList;
        } else {
            tmp = rList;
            tmp->previous->next = tmp->next;
            tmp->next->previous = tmp->previous;
            free(tmp);
            resetIndexes(rList);
        }
    } else {
        return (rList->next == NULL) ? rList : deleteInBulk(rList->next, movie_code);
    }

    return deleteInBulk(rList, movie_code);
}

NODE *deleteSingleMovie(NODE *pList, R_NODE *rList, int movie_code) {
    NODE *tmp = NULL;
    bool hasRatings;
    while (pList->next != NULL) {
        if (movie_code == pList->movie.Movie_code) {
            hasRatings = checkForRatings(rList, rList->rating.Movie_code);
            if (hasRatings) {
                rList = deleteInBulk(rList, movie_code);
            }

            if (pList->previous == NULL) {
                tmp = pList;
                pList = pList->next;
                pList->previous = NULL;
                free(tmp);
                resetMovieIndexes(pList);
            } else if (pList->next == NULL) {
                pList = pList->previous;
                pList->next = NULL;
                free(tmp);
            } else {
                tmp = pList;
                tmp->previous->next = tmp->next;
                tmp->next->previous = tmp->previous;
                free(tmp);
                resetMovieIndexes(pList);
            }
        }
        pList = pList->next;
    }
    return pList;
}

NODE *buildList(NODE *pList) {
    FILE *pM_Data;
    NODE *pPre = NULL;
    M_DATA movie;

    pM_Data = fopen("Movies.txt", "r");

    if (pM_Data == NULL) {
        printf("Error opening text file.\n");
        free(pM_Data);
        fclose(pM_Data);
        exit(100);
    }

    pPre = getM_Data(pM_Data, movie);
    pList = pPre;

    if (fclose(pM_Data) == EOF) {
        printf("Error closing text file\n");
        free(pM_Data);
        fclose(pM_Data);
        exit(300);
    }

    return pList;
}

R_NODE *buildR_List(R_NODE *rList) {
    FILE *pR_Data;
    R_NODE *pRatings = NULL;
    R_DATA rating;

    pR_Data = fopen("Ratings.txt", "r");

    if (pR_Data == NULL) {
        printf("Error opening text file.\n");
        exit(200);
    }

    pRatings = getR_Data(pR_Data, rating);
    rList = pRatings;

    if (fclose(pR_Data) == EOF) {
        printf("Error closing text file\n");
        exit(900);
    }

    return rList;
}

NODE *getM_Data(FILE *pM_Data, M_DATA movie) {
    NODE *list;

    if (!(list = (NODE *) malloc(sizeof(NODE)))) {
        printf("Memory overflow in insert\n");
        exit(400);
    }

    char Mfname[LENGTH_OF_CHAR];
    char Mlname[LENGTH_OF_CHAR];
    char director_Fname[LENGTH_OF_CHAR];
    char director_Lname[LENGTH_OF_CHAR];
    int numberOfLines = 0;

    while (fscanf(pM_Data, "%d %s %s %d %d %s %s", &movie.Movie_code, Mfname,
                  Mlname, &movie.year, &movie.length_of_movie, director_Fname, director_Lname) == 7) {
        movie = allocM_Data(Mfname, Mlname, director_Fname, director_Lname, movie);

//        printf("%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", movie.Movie_code, movie.Mfname, movie.Mlname,
//               movie.year, movie.length_of_movie, movie.director_Fname, movie.director_Lname);

        numberOfLines += 1;

        if (numberOfLines == 1) {
            list = makeNode(movie);
        } else { list = append(list, movie); }
    }

    return list;
}

R_NODE *getR_Data(FILE *pR_Data, R_DATA rating) {

    R_NODE *ratingsList;

    if (!(ratingsList = (R_NODE *) malloc(sizeof(R_NODE)))) {
        printf("Memory overflow in insert\n");
        exit(400);
    }

    char Rname[LENGTH_OF_CHAR];
    char status[LENGTH_OF_CHAR];

    int numberOfLines = 0;

    while ((fscanf(pR_Data, "%d %d %s %s %d", &rating.Ratings_id, &rating.Movie_code, Rname, status,
                   &rating.rating_value)) == 5) {
        rating = allocR_Data(Rname, status, rating);

        //printf("%3d %3d %-8s %-10s %d \n", rating.Ratings_id, rating.Movie_code, rating.Rname, rating.status,
        //rating.rating_value);

        numberOfLines += 1;

        if (numberOfLines == 1) {
            ratingsList = makeR_Node(rating);
        } else {
            appendR_Data(ratingsList, rating);
        }
    }

    return ratingsList;
}

NODE *makeNode(M_DATA line) {

    NODE *newNode = NULL;
    newNode = (NODE *) malloc(sizeof(NODE));

    if (newNode == NULL) {
        printf("Memory overflow in insert\n");
        exit(500);
    }

    newNode->movie = line;
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

R_NODE *makeR_Node(R_DATA line) {

    R_NODE *newNode = NULL;
    newNode = (R_NODE *) malloc(sizeof(R_NODE));

    if (newNode == NULL) {
        printf("Memory overflow in insert\n");
        exit(600);
    }

    newNode->rating = line;
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

NODE *append(NODE *head, M_DATA line) {
    if (head->next == NULL) {
        NODE *tmp = NULL;
        tmp = makeNode(line);
        tmp->next = NULL;
        tmp->previous = head;
        head->next = tmp;
        if (head->previous == NULL) {
            head->index = 1;
        }
        if (head->previous != NULL) { head->index = head->previous->index + 1; }
        return head;
    }

    append(head->next, line);
    while (head->next != NULL) {
        head = head->next;
        head->index = head->previous->index + 1;
    }//setting index of last element

    while (head->previous != NULL) {
        head = head->previous;
    }//going back to head
    return head;
}

void appendR_Data(R_NODE *head, R_DATA line) {

    if (head->next == NULL) {
        R_NODE *tmp = NULL;
        tmp = makeR_Node(line);
        tmp->next = NULL;
        tmp->previous = head;
        head->next = tmp;
        if (head->previous == NULL) {
            head->index = 1;
        } else { head->index = head->previous->index + 1; }
        return;
    }

    appendR_Data(head->next, line);
    while (head->next != NULL) {
        head = head->next;
        head->index = head->previous->index + 1;
    }//setting index of last element

    while (head->previous != NULL) {
        head = head->previous;
    }//going back to head
}

R_NODE *appendSingleR_Data(R_NODE *head, R_DATA line) {

    if (head->next == NULL) {
        R_NODE *tmp = NULL;
        tmp = makeR_Node(line);
        tmp->next = NULL;
        tmp->previous = head;
        head->next = tmp;
        return head;
    }
    return appendSingleR_Data(head->next, line);
}

R_NODE *sortR_Node(R_NODE *head, R_NODE *tail) {

    if (head == NULL) {
        return tail;
    }

    if (tail->rating.Movie_code == head->rating.Movie_code) {
        tail = appendSingleR_Data(tail, head->rating);
        return (head->next == NULL) ? tail : sortR_Node(head->next, tail);
    } else {
        return (head->next == NULL) ? tail : sortR_Node(head->next, tail);
    }
    //return tail;
}

NODE *changeM_Head(NODE *head, NODE *nextHead) {
    while (head->next != NULL && nextHead != NULL) {
        if (head->movie.Movie_code == nextHead->movie.Movie_code) {
            nextHead = nextHead->next;
            changeM_Head(head, nextHead);
        } else {
            return nextHead;
        }
    }
}

R_NODE *changeR_Head(R_NODE *head, R_NODE *nextHead) {
    while (head->next != NULL && nextHead != NULL) {
        if (head->rating.Movie_code == nextHead->rating.Movie_code) {
            nextHead = nextHead->next;
            changeR_Head(head, nextHead);
        } else {
            return nextHead;
        }
    }
}

NODE *addRatingsToMovies(NODE *movies, R_NODE *ratings) {
    if (movies == NULL) { return movies; }
    //don't forget to handle the null scenario for incoming movies and ratings
    if (movies->movie.Movie_code == ratings->rating.Movie_code) {
        movies->rating = ratings;
    } else {
        movies = changeM_Head(movies, movies->next);
        addRatingsToMovies(movies, ratings);
    }
    return movies;
}

void constructMainList(NODE *fullMovies, R_NODE *fullRatings) {

    if (fullMovies == NULL) { return; }//incase the list is empty

    R_NODE *truncatedRList = NULL;

    while (fullRatings->next != NULL && fullMovies->next != NULL) {
        truncatedRList = makeR_Node(fullRatings->rating);
        truncatedRList = sortR_Node(fullRatings->next, truncatedRList);
        fullMovies = addRatingsToMovies(fullMovies, truncatedRList);
        fullRatings = changeR_Head(fullRatings, fullRatings->next);
        constructMainList(fullMovies, fullRatings);
        break;
    }
}

NODE *prepend(NODE *head, M_DATA line) {

    NODE *newHead;

    if (head == NULL) {
        return makeNode(line);
    }

    newHead = makeNode(line);
    newHead->next = head;
    newHead->previous = NULL;
    newHead->index++;
    return newHead;
}

R_NODE *prependR_Data(R_NODE *head, R_DATA line) {

    R_NODE *newHead;

    if (head == NULL) {
        return makeR_Node(line);
    }

    newHead = makeR_Node(line);
    newHead->next = head;
    newHead->previous = NULL;
    newHead->index++;
    return newHead;
}

void printListAsc(NODE *pList) {
    printf("\nList contains:\n");

    if (pList == NULL) {
        printf("your list contains null\n");
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Movies Code\t Title \t\t Year \t Length \t Director \n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while (pList != NULL) {
        printf("%-5d %10s %-15s   %4d   %5d  %-12s %10s \n", pList->movie.Movie_code, pList->movie.Mfname,
               pList->movie.Mlname, pList->movie.year, pList->movie.length_of_movie, pList->movie.director_Fname,
               pList->movie.director_Lname);
        if (pList->rating != NULL) {
            printR_ListAsc(pList->rating); //CHCEK
        }
        pList = pList->next;
    }

    printf("<End of List>\n\n");
}

void printR_ListAsc(R_NODE *rList) {
    printf("\nRatings list contains:\n");

    if (rList == NULL) {
        printf("your list contains null\n");
    }

    while (rList->previous != NULL) {
        rList = rList->previous;
    }
    
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Review ID  Movie Code  Name  Status \t Ratings \n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while (rList != NULL) {
        printf("%-5d %10d %12s %-10s %3d\n", rList->rating.Ratings_id, rList->rating.Movie_code,
               rList->rating.Rname, rList->rating.status, rList->rating.rating_value);
        rList = rList->next;
    }

    printf("<End of List>\n\n");
}


void printM_ListAsc(NODE *pList) {
    printf("\nRatings list contains:\n");

    if (pList == NULL) {
        printf("your list contains null\n");
    }

    while (pList->previous != NULL) {
        pList = pList->previous;
    }
    
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Review ID  Movie Code  Name  Status \t Ratings \n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while (pList != NULL) {
        printf("%-5d %10s %-15s   %4d   %5d  %-12s %10s \n", pList->movie.Movie_code, pList->movie.Mfname,
               pList->movie.Mlname, pList->movie.year, pList->movie.length_of_movie, pList->movie.director_Fname,
               pList->movie.director_Lname);
        pList = pList->next;
    }

    printf("<End of List>\n\n");
}

void printMoviesToFile(NODE *pList, FILE *pM_Data) {
    while (pList->previous != NULL) {
        pList = pList->previous;
    }//go back to head of linked-list
	
	
	 
    while (pList != NULL) {
        fprintf(pM_Data, "%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", pList->movie.Movie_code, pList->movie.Mfname,
                pList->movie.Mlname, pList->movie.year, pList->movie.length_of_movie, pList->movie.director_Fname,
                pList->movie.director_Lname);
        pList = pList->next;
    }
}

void printRatingsToFile(R_NODE *pList, FILE *pR_Data) {
    while (pList->previous != NULL) {
        pList = pList->previous;
    }
    
    
    while (pList != NULL) {
        fprintf(pR_Data, "%3d %3d %-8s %-10s %d\n", pList->rating.Ratings_id, pList->rating.Movie_code,
                pList->rating.Rname, pList->rating.status, pList->rating.rating_value);
        pList = pList->next;
    }
}

void printListDesc(NODE *pList) {
    printf("\nList contains:\n");

    if (pList == NULL) {
        printf("your list contains null\n");
    }

    while (pList->next != NULL) {
        pList = pList->next;
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Movies Code \t Title \t\t\t   \t\t  Year \t\t\t Length \t\t Director \n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
	
    while (pList->previous != NULL) {
        printf("%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", pList->movie.Movie_code, pList->movie.Mfname,
               pList->movie.Mlname, pList->movie.year, pList->movie.length_of_movie, pList->movie.director_Fname,
               pList->movie.director_Lname);
        pList = pList->previous;
    }

    printf("<Beginning of List>\n\n");
}

bool searchByMovie_Code(NODE *pList, int movie_code) {
    while (pList != NULL) {
        if (movie_code == pList->movie.Movie_code) {
            return true;
        } else {
            return searchByMovie_Code(pList->next, movie_code);
        }
    }
    return false;
}

M_DATA getMovieByMovie_Code(NODE *pList, int movie_code) {
    while (pList != NULL) {
        if (movie_code == pList->movie.Movie_code) {
            return pList->movie;
        } else {
            return getMovieByMovie_Code(pList->next, movie_code);
        }
    }
}

bool searchByRating_Id(R_NODE *pList, int rating_id) {
    while (pList != NULL) {
        if (rating_id == pList->rating.Ratings_id) {
            return true;
        } else {
            return searchByRating_Id(pList->next, rating_id);
        }
    }
    return false;
}

R_DATA getRatingById(R_NODE *pList, int rating_id) {
    while (pList != NULL) {
        if (rating_id == pList->rating.Ratings_id) {
            return pList->rating;
        } else {
            return getRatingById(pList->next, rating_id);
        }
    }
}

int checkUserChoice(char *answer) {
    int asciiValue = (int) answer[0];
    if (asciiValue == 89 || asciiValue == 121) {
        return 1;
    }else if (asciiValue == 78 || asciiValue == 110) { return 0; }
    else return -1;
}

R_NODE *editRating(R_NODE *pList, int movie_code) {
    char Rname[LENGTH_OF_CHAR];
    char status[LENGTH_OF_CHAR];
    char answer[LENGTH_OF_CHAR];
    int rating_id;
    bool isRatingExists, isYes;
    R_DATA rating;
    R_DATA ratingDataFromList;
    
	do {
        printf("Please enter a rating_id:\n");
        scanf("%d", &rating_id);
        
        //isRatingExists = searchByRating_Id(pList, rating_id);
        ratingDataFromList = getRatingById(pList, rating_id);
        isRatingExists = movie_code == ratingDataFromList.Movie_code;
       /* if(isRatingExists){
        	isRatingExists = movie_code == ratingDataFromList.Movie_code;
		}*/
        if (!isRatingExists) {
            printf("This rating_id doesn't exist, please try another rating_id\n");
        }
    } while (!isRatingExists);
    
    printf("Is this the rating you wish to edit?[Y/N]\n");
    printf("%3d %3d %-8s %-10s   %d\n", ratingDataFromList.Ratings_id, ratingDataFromList.Movie_code,
        ratingDataFromList.Rname, ratingDataFromList.status, ratingDataFromList.rating_value);
    scanf("%s", answer);
    isYes = checkUserChoice(answer);
    if (!isYes) {
    	printf("Then the ratings sheet remains unchanged!");
		return pList;
	}

    rating.Ratings_id = rating_id;

    printf("Please enter the new username:\n");
    scanf("%s", Rname);

    printf("Please enter the new status of this user:\n");
    scanf("%s", status);

    printf("Please enter the new rating value:\n");
    scanf("%d", &rating.rating_value);

    rating = allocR_Data(Rname, status, rating);

    rating.Movie_code = movie_code;

    printf("Is this the new rating you wish to post?[Y/N]\n");
    printf("%3d %3d %-8s %-10s   %d\n", rating.Ratings_id, rating.Movie_code,
           rating.Rname, rating.status, rating.rating_value);
    scanf("%s", answer);
    isYes = checkUserChoice(answer);
    if (isYes) {
        while (pList != NULL) {
            if (rating_id == pList->rating.Ratings_id) {
                pList->rating = rating;
                return pList;
            }
            pList = pList->next;
        }
    } else {
        printf("Then the ratings sheet remains unchanged!");
        return pList;
    }
}

NODE *editMovie(NODE *pList, int movie_code) {

    char answer[LENGTH_OF_CHAR];
    bool isYes;

    M_DATA movie = getMovieData(movie_code);

    printf("Is this the update you wish to make?[Y/N]\n");
    printf("%3d %-8s %-10s   %4d   %3d  %-9s %-10s \n", movie.Movie_code, movie.Mfname,
           movie.Mlname, movie.year, movie.length_of_movie, movie.director_Fname,
           movie.director_Lname);
    scanf("%s", answer);
    isYes = checkUserChoice(answer);

    if (isYes) {
        while (pList != NULL) {
            if (movie_code == pList->movie.Movie_code) {
                pList->movie = movie;
                return pList;
            }
            pList = pList->next;
        }
    }
    return pList;
}

void addNewRating(R_NODE *pList, int movie_code) { //make rList
    char Rname[LENGTH_OF_CHAR];
    char status[LENGTH_OF_CHAR];
    int rating_id;
    bool isRatingExists;
    R_DATA rating;

    do {
        printf("Please enter a rating_id:\n");
        scanf("%d", &rating_id);
        isRatingExists = searchByRating_Id(pList, rating_id);
        if (isRatingExists) { printf("This rating_id already exists, rating_id must be unique\n"); }
        /*if (!isRatingExists) {
            rating.Ratings_id = rating_id;
        }*/
    } while (isRatingExists);
    
    rating.Ratings_id = rating_id;

    printf("Please enter the username:\n");
    scanf("%s", Rname);

    printf("Please enter the status of this user:\n");
    scanf("%s", status);

    rating = allocR_Data(Rname, status, rating);

    rating.Movie_code = movie_code;

    while (pList != NULL) {
        if (movie_code != pList->rating.Movie_code) {
            while (pList->next != NULL) {
                pList = pList->next;
            }
            pList = appendSingleR_Data(pList, rating);
        }
        pList = pList->next;
    }
}

R_DATA allocR_Data(char *Rname, char *status, R_DATA rating) {
    rating.Rname = malloc((strlen(Rname) + 1) * sizeof(char *));
    if (!rating.Rname) {
        free(rating.Rname);
        exit(110);
    }
    strcpy(rating.Rname, Rname);

    rating.status = malloc((strlen(status) + 1) * sizeof(char *));
    if (!rating.status) {
        free(rating.status);
        exit(120);
    }
    strcpy(rating.status, status);

    return rating;
}

void addNewMovie(NODE *pList, int movie_code) {
    char Mfname[LENGTH_OF_CHAR];
    char Mlname[LENGTH_OF_CHAR];
    char director_Fname[LENGTH_OF_CHAR];
    char director_Lname[LENGTH_OF_CHAR];
    NODE *tmp;
    M_DATA movie = getMovieData(movie_code);
    
    movie = allocM_Data(Mfname, Mlname, director_Fname, director_Lname, movie);
	
    tmp->movie = movie;
    while (pList->next != NULL) {
        if (pList->movie.Movie_code >= pList->next->movie.Movie_code) {
            pList = pList->next;
        }//if movie_code larger swap go to next node
        else {
            tmp->next = pList->next->next;
            pList->next = tmp;
            tmp->previous = pList;
            tmp->next->previous = tmp;
        }
    }

    printf("New movie entry added!\n");
}

M_DATA getMovieData(int movie_code) { //good
    char Mfname[LENGTH_OF_CHAR];
    char Mlname[LENGTH_OF_CHAR];
    char director_Fname[LENGTH_OF_CHAR];
    char director_Lname[LENGTH_OF_CHAR];
    M_DATA movie;

    movie.Movie_code = movie_code;

    printf("Please enter the new movie first name:\n");
    scanf("%s", Mfname);

    printf("Please enter the new movie last name:\n");
    scanf("%s", Mlname);

    printf("Please enter the new movie year:\n");
    scanf("%d", &movie.year);

    printf("Please enter the new movie length:\n");
    scanf("%d", &movie.length_of_movie);

    printf("Please enter the new director first name:\n");
    scanf("%s", director_Fname);

    printf("Please enter the new director last name:\n");
    scanf("%s", director_Lname);

    movie = allocM_Data(Mfname, Mlname, director_Fname, director_Lname, movie);

    return movie;
}

M_DATA allocM_Data(char *Mfname, char *Mlname, char *director_Fname, char *director_Lname,
                   M_DATA movie) {
    movie.Mfname = calloc(strlen(Mfname) + 1, sizeof(char));
    if (!movie.Mfname) {
        free(movie.Mfname);
        exit(9);
    }
    strcpy(movie.Mfname, Mfname);

    movie.Mlname = calloc(strlen(Mlname) + 1, sizeof(char));
    if (!movie.Mlname) {
        free(movie.Mlname);
        exit(10);
    }
    strcpy(movie.Mlname, Mlname);

    movie.director_Fname = calloc(strlen(director_Fname) + 1, sizeof(char));
    if (!movie.director_Fname) {
        free(movie.director_Fname);
        exit(11);
    }
    strcpy(movie.director_Fname, director_Fname);

    movie.director_Lname = calloc(strlen(director_Lname) + 1, sizeof(char));
    if (!movie.director_Lname) {
        free(movie.director_Lname);
        exit(12);
    }
    strcpy(movie.director_Lname, director_Lname);

    return movie;
}

NODE *getratingsUnderAMovie(NODE *fullMovies, R_NODE *fullRatings, int movie_code) {

    R_NODE *truncatedRList = NULL;
    NODE *movie = NULL;
	
	if (fullMovies == NULL) { return fullMovies; }//incase the list is empty

    while(fullMovies != NULL){
        if(movie_code == fullMovies->movie.Movie_code){
            movie = makeNode(fullMovies->movie);
            while(fullRatings->next != NULL){
                if(movie_code == fullRatings->rating.Movie_code){
                    
					if(truncatedRList == NULL){
						truncatedRList = makeR_Node(fullRatings->rating);
					}
                    
                }
                truncatedRList = sortR_Node(fullRatings, truncatedRList);                   					                    
				
                fullRatings = fullRatings->next;
            }            
        }
        fullMovies = fullMovies->next;
    }
    
    movie = addRatingsToMovies(movie, truncatedRList);
    
    return movie;
}


void Searchfunction(NODE *pList )
{
    int i=0;
    int length_movie =0;
    int x,y =0;
    int option=0;
    int selection=0;
	int found =0;

    do {
        printf("---------------------------------------------------------------------------------------------------------------\n");
        printf("\nPlease enter one of the next options: 1, 2 or 0\n");
        printf("1: Search by Movies shorter or longer than:\n");
        printf("2: Search by Movies in between a specified range: \n");
        printf("0: Exit\n");
        scanf("%d",&selection);

        switch (selection)
        {
        	
          case 1:
            printf("Enter the length: \n");
            scanf("%d",&length_movie);

            do {

                printf("\nPlease enter one of the next options: 1, 2 or 0\n");
                printf("1: Display Movies shorter than Entered length \n");
                printf("2: Display Movies Longer than Entered length\n");
                printf("0: Exit\n");
                printf("---------------------------------------------------------------------------------------------------------------\n");

                scanf("%d", &option);

                switch (option)
                {

                case 1:
                    printf("These are movies shorter than selection:\n");
                    printf("  Movies \t\tLength\n");
					found =0;
                    while(pList->next  != NULL)
                    {
                        if (pList->movie.length_of_movie < length_movie)
                        { 
							found =1;
                            printf("%-10s %-12s  %5d \n",pList->movie.Mfname ,pList->movie.Mlname,pList->movie.length_of_movie);
                        }
						pList=pList->next;
                    }
                    if(!found)
                    {
                        printf("Not in range!\n");
                    }
                break;

                case 2:
                    printf("These are movies Longer than selection:\n");
                    printf("   Movies \t\tLength\n");
                    found =0;
                    while(pList->next != NULL)
                    {
                        if (pList->movie.length_of_movie>length_movie)
                        {	
                     	   found =1;
                           printf("%-10s %-12s  %5d \n",pList->movie.Mfname ,pList->movie.Mlname,pList->movie.length_of_movie);
                        }
                        pList=pList->next;
                    }
                    if(!found)
                    {
                        printf("Not in range!\n");
                    }


                    break;

                default:

                    printf("Not in Parameter!\n");

                }
                
          break;

					 
            } while (option !=0);
        
      	 case 2:

            printf("Enter the range of values:\n");
            printf("X(lower boundary) :");
            scanf("%d",&x);
            printf("\nY (high boundary) :");
            scanf("%d",&y);
           	found =0;
            printf(" Movies \t\t\t Length\n");
            while(pList->next  != NULL)
            {
                if ( x <= pList->movie.length_of_movie && y >=pList->movie.length_of_movie)
                {	
                	found =1;                   
                    printf(" %-10s %-10s\t   %5d \n",pList->movie.Mfname ,pList->movie.Mlname,pList->movie.length_of_movie);
                }
                pList=pList->next;
            }
            if(!found)
            {
                printf("Not iin range!\n");
            }
            
            break;
        
        case 0:
        	exit(1);
        
        default:
        
            printf("Not a Parameter \n");

	}	
		
    } while(selection!=0);

  
}


void freeMovieList(NODE *fullmovie) {
    NODE *nexthead = NULL;
    while (fullmovie != NULL) {
        nexthead = fullmovie->next;
        if (fullmovie->rating != NULL) 
		{ 
		freeRatingList(fullmovie->rating);
		 }
		 
		 free(fullmovie->movie.director_Fname);
		 free(fullmovie->movie.director_Lname);
		 free(fullmovie->movie.Mfname);
		 free(fullmovie->movie.Mlname);
		     	
        free(fullmovie);
        fullmovie = nexthead;
    }
}

void freeRatingList(R_NODE *fullRatings) {
    R_NODE *nextHead = NULL;
    while (fullRatings != NULL) {
        nextHead = fullRatings->next;
        free(fullRatings->rating.Rname);
        free(fullRatings->rating.status);
        free(fullRatings);
        fullRatings = nextHead;
    }
}

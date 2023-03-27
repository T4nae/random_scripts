/*
 *  COURIER MANAGEMENT SYSTEM
 * - This is a simple courier management system which can be used by a courier company to manage their parcels.
 * - It has two portals, one for customers and one for admin.
 * - Customers can send a parcel and track it.
 * - Admin can view all the parcels, delete a parcel, update a parcel and search for a parcel.
 * - All the data is stored in a file named parcels.txt.
 * - The file is created if it does not exist.
 * - The file is initialized with default admin credentials.
 * - The admin can also change the status of a parcel.
 * - The admin can also sort the parcels by weight.
 * - The admin can also search for a parcel by id, name, weight, address, phone, email, date and time and status.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

// function prototypes
void customer_portal();
void send_parcel();
void track();
void admin_portal();
int login();
FILE *copy(FILE *file1);
void delete_parcel(int id);
void update(int id);
void sort();
void search();

// global variables and structs
const int size = 100;                        // max number of parcels
char user[10] = "admin", pass[10] = "admin"; // default admin credentials
struct parcel
{
    int id;
    char name[20];
    float weight;
    char address[50];
    char phone[11];
    char email[20];
    char status[10];
    char date_time[30];
};

// utility function to display parcel
void display(parcel out)
{
    printf("Parcel id: %d\n", out.id);
    printf("Name: %s\n", out.name);
    printf("Weight: %f kg\n", out.weight);
    printf("Address: %s\n", out.address);
    printf("Phone: %s\n", out.phone);
    printf("Email: %s\n", out.email);
    printf("DateTime: %s\n", out.date_time);
    printf("Status of Parcel: %s\n", out.status);
    printf("--------------------------------------------\n");
}
// initialize file if not exists
int initialize()
{
    FILE *t;
    t = fopen("parcels.txt", "r");
    if (t == NULL)
    {
        t = fopen("parcels.txt", "w");
        if (t == NULL)
        {
            printf("Error Initializing\n");
            return 0;
        }
    }
    fclose(t);
    printf("Successfully initialized\n\n");
    return 1;
}

// main function
main()
{
    int ch = initialize(); // choice variable gets value of 1 if initialization is successful else 0
    // main menu loop
    while (ch)
    {
        printf("\e[1;1H\e[2J"); // clears screen
        printf("1. Customer Portal\n2. Admin Portal\n0. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            customer_portal();
            break;
        case 2:
            admin_portal();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}

// sub loop for customer portal menu
void customer_portal()
{
    int ch = 1;             // choice variable
    printf("\e[1;1H\e[2J"); // clears screen
    while (ch)
    {
        printf("1. Send a parcel\n2. Track a parcel\n0. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            // clear screen and send a parcel
            printf("\e[1;1H\e[2J");
            printf("Fill Details of Parcel\n\n");
            send_parcel();
            break;
        case 2:
            // clear screen and track a parcel
            printf("\e[1;1H\e[2J");
            track();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}

// function to send a parcel from customer portal and save details in file
void send_parcel()
{
    // find empty id to store new parcel details
    parcel inp;                                // input structure to store store data while accessing or writing to file
    inp.id = 0;                                // setting default value incase file is empty
    FILE *pa;                                  // file pointer points to
    pa = fopen("parcels.txt", "a+");           // opens existing file in append and read mode
    while (fread(&inp, sizeof(parcel), 1, pa)) // loops until parcels in file
    {
        inp.id++; // incrementing the last ID (all values except last will replace this value leaving us with last ID + 1)
    }
    // if nothing exists in file value of id would be 0 so we set it to 1
    if (inp.id == 0)
    {
        inp.id = 1;
    }

    // Enter details of Parcel
    fflush(stdin); // clear input buffer to avoid errors
    printf("Enter address: \n");
    gets(inp.address);
    printf("Enter name: \n");
    scanf("%s", &inp.name);
    printf("Enter weight in kgs: \n");
    scanf("%f", &inp.weight);
    printf("Enter phone: \n");
    scanf("%s", &inp.phone);
    printf("Enter email: \n");
    scanf("%s", &inp.email);
    strcpy(inp.status, "pending");

    // Exact dateTime when Parcel is Received
    time_t raw_time;
    tm *info;
    time(&raw_time);
    info = localtime(&raw_time);
    strcpy(inp.date_time, asctime(info));

    // append details to file and close
    fwrite(&inp, sizeof(parcel), 1, pa);
    fclose(pa);
    // clear screen and display tracking id
    printf("\e[1;1H\e[2J");
    printf("Tracking ID of your parcel is: %d\n\n", inp.id);
}

// function to track a parcel from customer portal
void track()
{
    parcel out;
    FILE *pa;
    // id of the parcel to be tracked
    int id;
    printf("Enter parcel id: ");
    scanf("%d", &id);
    // clear screen
    printf("\e[1;1H\e[2J");
    // find parcel with given id
    pa = fopen("parcels.txt", "r");            // open file in read mode
    while (fread(&out, sizeof(parcel), 1, pa)) // loops until parcels in file
    {
        if (out.id == id) // breaks only if parcel is found in file
        {
            break;
        }
    }
    // displays the parcel data if exists in file
    if (out.id == id)
    {
        // print parcel details
        display(out);
    }
    else
    {
        printf("Parcel does not exist\n");
    }
}

// sub loop for admin portal menu
void admin_portal()
{
    int ch = login();       // choice variable gets value of 1 if login is successful else 0
    printf("\e[1;1H\e[2J"); // clears screen
    while (ch)
    {
        printf("1. Delete/Update parcel\n2. Display all parcels\n3. Sort parcel\n4. Search parcel\n0. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            // clear screen and get id of the parcel to delete
            printf("\e[1;1H\e[2J");
            int id, c;
            printf("\nEnter parcel ID to Delete/Update: ");
            scanf("%d", &id);
            // get option to delete or update
            printf("1. Delete\n2. Update\n0. Exit\nEnter Choice: ");
            scanf("%d", &c);
            switch (c)
            {
            case 1:
                delete_parcel(id);
                break;
            case 2:
                update(id);
                break;
            default:
                printf("Exiting...\n");
                break;
            }
            break;
        case 2:
            // clear screen and display all parcels
            printf("\e[1;1H\e[2J");
            printf("All parcels: \n\n");
            FILE *pa;
            parcel out;
            pa = fopen("parcels.txt", "r");            // open parcel file in read mode
            while (fread(&out, sizeof(parcel), 1, pa)) // loop until parcel in parcels
            {
                display(out); // display parcel details
            }
            fclose(pa);
            break;
        case 3:
            printf("\e[1;1H\e[2J");
            sort();
            break;
        case 4:
            printf("\e[1;1H\e[2J");
            search();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        }
    }
}

// login function for admin portal
int login()
{
    char u[10], p[10]; // user and password variables
    printf("Enter user:\n");
    scanf("%s", &u);
    printf("Enter password:\n");
    scanf("%s", &p);
    // strcmp is a function that compares two strings and returns 0 if they are equal so !(strcmp) is 1 if they are equal
    if (!(strcmp(u, user)) && !(strcmp(p, pass))) // if user and password match the default credentials
    {
        printf("Access Granted\n");
        return 1;
    }
    else
    {
        printf("Access Denied\n");
        return 0;
    }
}

// utility function that receives main file in read mode then copies and returns a temporary pointer to it
FILE *copy(FILE *file1)
{
    fseek(file1, 0, SEEK_SET); // set cursor to start of file
    FILE *temp;
    parcel out;
    char c;

    // create a temporary copy of original file
    temp = fopen("temp.txt", "w+"); // opening a new file in write read mode
    c = fgetc(file1);               // gets 1 char at a time from file
    while (c != EOF)                // loops until End Of File is reached
    {
        fputc(c, temp);   // puts 1 char at a time in file
        c = fgetc(file1); // gets next char in the file
    }
    // close the main file and go to beginning of temp file
    fclose(file1);
    fseek(temp, 0, SEEK_SET);
    return temp;
}

// delete parcel function for admin portal
// to delete a entry in file we have to make a copy of original file
// then move everything to original file except the line to be deleted
void delete_parcel(int id)
{
    FILE *temp, *pa;
    parcel out;
    temp = copy(fopen("parcels.txt", "r")); // returns copy of main file
    pa = fopen("parcels.txt", "w");
    // get parcels from temp file and overwrite in main file except the parcel to be deleted
    while (fread(&out, sizeof(parcel), 1, temp))
    {
        if (out.id != id)
        {
            fwrite(&out, sizeof(parcel), 1, pa);
        }
    }
    fclose(temp);           // close the temp file
    remove("temp.txt");     // delete the temp file
    fclose(pa);             // close the main file
    printf("\e[1;1H\e[2J"); // clears screen
    printf("Successfully deleted\n");
}

// function to update status for admin portal
// to update a entry in file we have to make a copy of original file
// then move everything to original file and update the req parcel then move it as well
// then delete the temp file and close the main file
void update(int id)
{
    FILE *temp, *pa;
    parcel out, in;
    int i = 0, ch;

    // get choice from user
    printf("1. update status\n2. update weight\n3. update address\n4. update phone\n5. update email\n0. Exit\nEnter choice: ");
    scanf("%d", &ch);
    // save the parcel info to be updated in a parcel struct in
    switch (ch)
    {
    case 1:
        printf("Enter new status: ");
        scanf("%s", &in.status);
        break;
    case 2:
        printf("Enter new weight: ");
        scanf("%f", &in.weight);
        break;
    case 3:
        fflush(stdin); // clear input buffer to avoid errors
        printf("Enter new address: ");
        gets(in.address);
        break;
    case 4:
        printf("Enter new phone: ");
        scanf("%s", &in.phone);
        break;
    case 5:
        printf("Enter new email: ");
        scanf("%s", &in.email);
        break;
    case 0:
        break;
    default:
        break;
    }

    // check if parcel exists in file and update it
    temp = copy(fopen("parcels.txt", "r")); // returns copy of main file
    pa = fopen("parcels.txt", "w");
    // get parcels from temp file and overwrite in main file except the parcel to be updated
    while (fread(&out, sizeof(parcel), 1, temp))
    {
        if (out.id == id)
        {
            i = 1;
            // update the parcel
            // switch case used 2nd time in order to keep shorten the time temp file is open
            // strcpy is used to copy strings (to, from)
            switch (ch)
            {
            case 1:
                strcpy(out.status, in.status);
                break;
            case 2:
                out.weight = in.weight;
                break;
            case 3:
                strcpy(out.address, in.address);
                break;
            case 4:
                strcpy(out.phone, in.phone);
                break;
            case 5:
                strcpy(out.email, in.email);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
        }
        fwrite(&out, sizeof(parcel), 1, pa); // write the parcel to main file (updated or not)
    }

    // if parcel is found then i will be 1
    if (i)
    {
        printf("\e[1;1H\e[2J"); // clears screen
        printf("Successfully updated\n");
    }
    else
    {
        printf("\e[1;1H\e[2J"); // clears screen
        printf("Parcel not found\n");
    }

    fclose(temp);       // close the temp file
    remove("temp.txt"); // delete the temp file
    fclose(pa);         // close the main file
}

// sorts the parcels in file by weight or date or id
// we have to make a copy of original file
// then use bubble sort to sort the parcels in another temp file
// then move everything from temp file to copy of original file
// repeat until all parcels are sorted by weight
// then display the sorted parcels and delete the temp files
void sort()
{
    // counter for number of swaps, swapped for checking if any swap was made, length for length of list
    int counter, swapped = 1, length = 0;
    FILE *temp1, *temp2;
    parcel p1, p2;

    // find length of list
    FILE *pa;
    pa = fopen("parcels.txt", "r");
    while (fread(&p1, sizeof(parcel), 1, pa))
    {
        length++; // increment length for each parcel
    }
    temp1 = copy(pa);                 // copy of original file (temp.txt)
    temp2 = fopen("temp2.txt", "w+"); // second temp file (temp2.txt)
    while (swapped)                   // while any swap is made (default is 1)
    {
        swapped = 0; // set swapped to 0 to check if any swap is made in this iteration
        counter = 0; // reset counter to 0
        // get first parcel from temp file
        fread(&p1, sizeof(parcel), 1, temp1);
        while (counter < length - 1) // loop until all parcels are compared
        {
            // get next parcel to previous parcel
            fread(&p2, sizeof(parcel), 1, temp1);
            // compare parcels
            if (p1.weight > p2.weight)
            {
                fwrite(&p2, sizeof(parcel), 1, temp2); // write p2 parcel in temp2 file
                swapped = 1;                           // set swapped to 1 to indicate a swap was made
            }
            else
            {
                fwrite(&p1, sizeof(parcel), 1, temp2); // write p1 parcel in temp2 file
                p1 = p2;                               // set p1 to p2 to compare next parcel with it
            }
            counter++; // increment counter for each comparison
        }
        // write last parcel in temp2 file
        fwrite(&p1, sizeof(parcel), 1, temp2);

        // swap temp1 and temp2 files
        fclose(temp1);                    // close temp1 file
        fclose(temp2);                    // close temp2 file
        remove("temp.txt");               // delete temp1 file
        rename("temp2.txt", "temp.txt");  // rename temp2 file to temp1
        temp1 = fopen("temp.txt", "r");   // open temp1 file in read mode
        temp2 = fopen("temp2.txt", "w+"); // open temp2 file in write mode
    }
    // close both files
    fclose(temp1);
    fclose(temp2);
    // delete temp2 file
    remove("temp2.txt");
    // open temp1 file in read mode
    temp1 = fopen("temp.txt", "r");
    // display sorted parcels
    printf("sorted parcels:\n\n");
    while (fread(&p1, sizeof(parcel), 1, temp1))
    {
        display(p1); // display parcel
    }
    // close temp1 file
    fclose(temp1);
    // delete temp1 file
    remove("temp.txt");
}

// function for admin portal to search parcels by any atrributes
void search()
{
    int ch;
    parcel out;
    FILE *pa;
    // display menu
    printf("1. Search by id\n2. Search by name\n3. Search by weight\n4. Search by address\n5. Search by phone\n6. Search by email\n7. Search by date\n8. Search by status\n0. Exit\nEnter your choice: ");
    scanf("%d", &ch);
    pa = fopen("parcels.txt", "r");
    // switch case for different search options
    switch (ch)
    {
    case 1:
        // search by id
        int id;
        printf("Enter id: ");
        scanf("%d", &id);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (out.id == id)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }

        break;
    case 2:
        // search by name
        char name[20];
        printf("Enter name: ");
        scanf("%s", &name);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.name, name) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 3:
        // search by weight
        float weight;
        printf("Enter weight: ");
        scanf("%f", &weight);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (out.weight == weight)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 4:
        // search by address
        char address[50];
        printf("Enter address: ");
        scanf("%s", &address);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.address, address) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 5:
        // search by phone
        char phone[10];
        printf("Enter phone: ");
        scanf("%s", &phone);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.phone, phone) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 6:
        // search by email
        char email[20];
        printf("Enter email: ");
        scanf("%s", &email);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.email, email) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 7:
        // search by date
        char date_time[20];
        printf("Enter date: ");
        scanf("%s", &date_time);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.date_time, date_time) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 8:
        // search by status
        char status[20];
        printf("Enter status: ");
        scanf("%s", &status);
        while (fread(&out, sizeof(parcel), 1, pa)) // loops until end of file
        {
            if (strcmp(out.status, status) == 0) // compare strings using strcmp (returns 0 if strings are equal)
            {
                printf("\e[1;1H\e[2J"); // clear screen
                display(out);           // display parcel
            }
        }
        break;
    case 0:
        printf("Exiting...\n");
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    fclose(pa); // close file
}

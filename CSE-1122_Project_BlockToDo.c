#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#ifdef _WIN32
#include<windows.h>
#define CLEAR_SCREEN "cls"
#else
#include<unistd.h>
#define CLEAR_SCREEN "clear"
#endif

struct Task {
    int idx;
    char title[100];
    int block, blockm;
    int status;
    int h, m, s, ms;
};

struct Task tasks[9];
int task_count = 0;

void appTitle(){
    printf("\n");
    for(int i = 0; i < 70; i++) printf(" ");
    printf("Block ToDo\n\n");
}

void totalBlock(){
    int totalBlock = 0;
    int totalBlockm = 0;
    int trackedBlockh = 0;
    int trackedBlockm = 0;
    int trackedBlocks = 0;
    for(int i = 0; i < task_count; i++){
        totalBlock += tasks[i].block;
        totalBlockm += tasks[i].blockm;
        trackedBlockh += tasks[i].h;
        trackedBlockm += tasks[i].m;
        trackedBlocks += tasks[i].s;
    }

    if(trackedBlocks > 59){
        trackedBlockm += trackedBlocks / 60;
        trackedBlocks = trackedBlocks % 60;
    }

    if(trackedBlockm > 59){
        trackedBlockh += trackedBlockm / 60;
        trackedBlockm = trackedBlockm % 60;
    }

    if(totalBlockm > 59){
        totalBlock += totalBlockm / 60;
        totalBlockm = totalBlockm % 60;
    }
    printf("                                                             Total Blocks : %02d:%02d / %02d:%02d\n\n", trackedBlockh, trackedBlockm, totalBlock, totalBlockm);
}

void display_tasks(int index) {
    printf(" ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");
    printf("| Index |                                                Task                                                  | Block |    Status    | Time Tracked |\n");
    printf(" ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");
    for (int i = 0; i < task_count; i++) {
        printf("|   %d   | ", tasks[i].idx + 1);
        printf("%s", tasks[i].title);
        int n = 101 - strlen(tasks[i].title);
        for(int i = 0; i < n; i++) printf(" ");
        if(tasks[i].block > 0 || tasks[i].blockm > 0 ){
            printf("| %02d:%02d |", tasks[i].block, tasks[i].blockm);
        }
        else{
            printf("|      |");
        }
        if(tasks[i].status == 0){
            printf(" Not Started  |");
        }
        else if(tasks[i].status == 1){
            printf(" In Progress  |");
        }
        else if(tasks[i].status == 2){
            printf("     Done     |");
        }
        else if(tasks[i].status == 3){
            printf("    Dropped   |");
        }
        if(tasks[i].s > 0) printf("   %02d:%02d:%02d   |", tasks[i].h, tasks[i].m, tasks[i].s);
        else printf("              |");
        printf("\n ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");
    }
}

void display_task(int index) {
    index -= 1;
    printf(" ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");
    printf("| Index |                                                Task                                                  | Block |    Status    | Time Tracked |\n");
    printf(" ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");

    printf("|   %d   | ", tasks[index].idx + 1);
    printf("%s", tasks[index].title);
    int n = 101 - strlen(tasks[index].title);
    for(int i = 0; i < n; i++) printf(" ");
    if(tasks[index].block > 0 || tasks[index].blockm > 0 ){
        printf("| %02d:%02d |", tasks[index].block, tasks[index].blockm);
    }
    else{
        printf("|      |");
    }
    if(tasks[index].status == 0){
        printf(" Not Started  |");
    }
    else if(tasks[index].status == 1){
        printf(" In Progress  |");
    }
    else if(tasks[index].status == 2){
        printf("     Done     |");
    }
    else if(tasks[index].status == 3){
        printf("    Dropped   |");
    }
    if(tasks[index].s > 0) printf("   %02d:%02d:%02d   |", tasks[index].h, tasks[index].m, tasks[index].s);
    else printf("              |");
    printf("\n ------- ------------------------------------------------------------------------------------------------------ ------- -------------- -------------- \n");
}

void main_menu() {
    if(task_count > 0){
        totalBlock();
        display_tasks(task_count);
    }
    else{
        printf(" ----------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|                                                                   Task List Empty                                                                  |\n");
        printf(" ----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    printf("\n ---------------- ------------- ---------------- ---------------- ---------\n");
      printf("| 1. Select Task | 2. Add Task | 3. Update Task | 4. Delete Task | 5. Exit |");
    printf("\n ---------------- ------------- ---------------- ---------------- ---------");
}

void load_tasks() {
    FILE *file = fopen("block.db", "r");
    if (file == NULL) {
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, ",");
        tasks[task_count].idx = atoi(token);
        token = strtok(NULL, ",");
        strcpy(tasks[task_count].title, token);
        token = strtok(NULL, ",");
        tasks[task_count].block = atoi(token);
        token = strtok(NULL, ",");
        tasks[task_count].blockm = atoi(token);
        token = strtok(NULL, ",");
        tasks[task_count].h = atol(token);
        token = strtok(NULL, ",");
        tasks[task_count].m = atol(token);
        token = strtok(NULL, ",");
        tasks[task_count].s = atol(token);
        token = strtok(NULL, ",");
        tasks[task_count].ms = atol(token);
        token = strtok(NULL, ",");
        tasks[task_count].status = atoi(token);

        task_count++;
    }
    fclose(file);
}

void save_tasks() {
    FILE *file = fopen("block.db", "w");
    if (file == NULL) {
        printf("Database Error.\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d,%s, %d, %d, %d, %d, %d, %d, %d\n", i, tasks[i].title, tasks[i].block, tasks[i].blockm, tasks[i].h, tasks[i].m, tasks[i].s, tasks[i].ms, tasks[i].status);
    }
    fclose(file);
}

void clear_console() {
    save_tasks();
    system(CLEAR_SCREEN);
    appTitle();
}

int main(){
    system(CLEAR_SCREEN);
    printf("\n");
    for(int i = 0; i < 70; i++) printf(" ");
    printf("Block ToDo\n\n");

    for(int i = 0; i < (70 - (19/2)); i++) printf(" ");
    printf(" ---------------------------\n");
    for(int i = 0; i < (70 - (19/2)); i++) printf(" ");
    printf("| unblock your productivity |\n");
    for(int i = 0; i <(70 - (19/2)); i++) printf(" ");
    printf(" ---------------------------\n\n");

    load_tasks();
    int choice;
    while(1){
        main_menu();
        printf("\n| Option: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                if (task_count == 0) {
                    clear_console();
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf("| there are no tasks |\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n\n");
                    break;
                }
                clear_console();
                display_tasks(task_count);
                int task_index;
                printf("| Task Index: ");
                scanf("%d", &task_index);

                if (task_index > 0 && task_index <= task_count) {
                    clear_console();

                    int timer_choice;
                    display_task(task_index);
                    printf("\n ----------------\n| 1. Start Timer |\n ----------------\n");
                    printf("| Option: ");
                    scanf("%d", &timer_choice);
                    display_task(task_index);
                    task_index--;
                    if (timer_choice == 1) {
                        clear_console();
                        printf("| Task: %s\n\n", tasks[task_index].title);
                        printf("---------- ----------\n");
                        printf(" Tracked  |   Block \n");
                        printf("---------- ----------\n");
                        while(1){
                            printf("\r%02d:%02d:%02d  |  %02d:%02d:00", tasks[task_index].h, tasks[task_index].m, tasks[task_index].s, tasks[task_index].block, tasks[task_index].blockm);
                            tasks[task_index].ms++;
                            Sleep(10);
                            if(tasks[task_index].ms == 100){
                                tasks[task_index].s++;
                                tasks[task_index].ms = 0;
                            }
                            if(tasks[task_index].s == 60){
                                tasks[task_index].m++;
                                tasks[task_index].s = 0;
                            }
                            if(tasks[task_index].m == 60){
                                tasks[task_index].h++;
                                tasks[task_index].m = 0;
                            }
                            if(kbhit()){
                                clear_console();
                                break;
                            }
                        }
                        int status_choice;
                        printf(" ---------------------------------------\n");
                        printf("|             Update Status             |\n");
                        printf(" --------- ---------------- ------------\n");
                        printf("| 1. Done | 2. In Progress | 3. Dropped |\n");
                        printf(" --------- ---------------- ------------\n");
                        printf("| Option:");
                        scanf("%d", &status_choice);
                        if (status_choice >= 1 && status_choice <= 3) {
                            if(status_choice == 1) tasks[task_index].status = 2;
                            if(status_choice == 2) tasks[task_index].status = 1;
                            if(status_choice == 3) tasks[task_index].status = 3;
                            clear_console();
                            for(int i = 0; i < (70 - (7 / 2)); i++) printf(" ");
                            printf(" --------------\n");
                            for(int i = 0; i < (70 - (7 / 2)); i++) printf(" ");
                            printf("| task updated |\n");
                            for(int i = 0; i < (70 - (7 / 2)); i++) printf(" ");
                            printf(" --------------\n\n");
                        } else {
                            tasks[task_index].status = 1;
                            clear_console();
                            for(int i = 0; i < (70 - (15 / 2)); i++) printf(" ");
                            printf(" ----------------------\n");
                            for(int i = 0; i < (70 - (15 / 2)); i++) printf(" ");
                            printf("| task updated default |\n");
                            for(int i = 0; i < (70 - (15 / 2)); i++) printf(" ");
                            printf(" ----------------------\n\n");
                        }
                    } else {
                        clear_console();
                        printf("                                                                ----------------------\n");
                        printf("                                                               | invalid timer choice |\n");
                        printf("                                                                ----------------------\n\n");
                    }
                } else {
                    clear_console();
                    printf("                                                                  --------------------\n");
                    printf("                                                                 | invalid task index |\n");
                    printf("                                                                  --------------------\n\n");
                }
                break;
            case 2:
                if (task_count < 100) {
                    char s[6];
                    clear_console();
                    tasks[task_count].idx = task_count;
                    printf("| Task Title: ");
                    scanf(" %[^\n]s", tasks[task_count].title);

                    printf("| Block     : ");
                    scanf(" %[^\n]s", &s);

                    int l = strlen(s);
                    if(l == 1){
                        tasks[task_count].block = s[0] - '0';
                        tasks[task_count].blockm = 0;
                    }
                    else if(l == 2){
                        tasks[task_count].block = ((s[0] - '0') * 10) + ((s[1] - '0') * 1);
                        tasks[task_count].blockm = 0;
                    }
                    else if(l == 3){
                        tasks[task_count].blockm = ((s[1] - '0') * 10) + ((s[2] - '0') * 1);
                        tasks[task_count].block = 0;
                    }
                    else if(l == 4){
                        tasks[task_count].block = ((s[0] - '0') * 1);
                        tasks[task_count].blockm = ((s[2] - '0') * 10) + ((s[3] - '0') * 1);
                    }
                    else{
                        tasks[task_count].block = ((s[0] - '0') * 10) + ((s[1] - '0') * 1);
                        tasks[task_count].blockm = ((s[3] - '0') * 10) + ((s[4] - '0') * 1);
                    }

                    if(tasks[task_count].blockm > 59){
                        tasks[task_count].block += tasks[task_count].blockm / 60;
                        tasks[task_count].blockm = tasks[task_count].blockm % 60;
                    }

                    tasks[task_count].h = 0;
                    tasks[task_count].m = 0;
                    tasks[task_count].s = 0;
                    tasks[task_count].ms = 0;
                    tasks[task_count].status = 0;

                    task_count++;

                    clear_console();
                    printf("                                                                   ----------------\n");
                    printf("                                                                  | new task added |\n");
                    printf("                                                                   ----------------\n\n");
                } else {
                    clear_console();
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf("| task limit reached |\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n\n");
                }
                break;
            case 3:
                if (task_count == 0) {
                    clear_console();
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf("| there are no tasks |\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n\n");
                    break;
                }
                clear_console();
                display_tasks(task_count);
                int update_index;
                printf("| Task Index: ");
                scanf("%d", &update_index);

                if (update_index >= 1 && update_index <= task_count) {
                    clear_console();
                    display_task(update_index);
                    printf("\n ----------------- ----------------- ------------------ ---------------\n");
                    printf("| 1. Update Title | 2. Update Block | 3. Update Status | 4. Reset Time |\n");
                    printf(" ----------------- ----------------- ------------------ ---------------\n");
                    int update_choice;
                    printf("Option: ");
                    scanf("%d", &update_choice);
                    switch (update_choice) {
                        case 1:
                            clear_console();
                            display_task(update_index);
                            printf("| New Task Title: ");
                            scanf(" %[^\n]s", tasks[update_index - 1].title);
                            clear_console();
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf(" --------------------\n");
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf("| task title updated |\n");
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf(" --------------------\n\n");
                            break;
                        case 2:
                            clear_console();
                            display_task(update_index);
                            printf("| New Block: ");

                            char s[6];
                            scanf(" %[^\n]s", &s);

                            int l = strlen(s);
                            if(l == 1){
                                tasks[update_index - 1].block = s[0] - '0';
                                tasks[update_index - 1].blockm = 0;
                            }
                            else if(l == 2){
                                tasks[update_index - 1].block = ((s[0] - '0') * 10) + ((s[1] - '0') * 1);
                                tasks[update_index - 1].blockm = 0;
                            }
                            else if(l == 3){
                                tasks[update_index - 1].blockm = ((s[1] - '0') * 10) + ((s[2] - '0') * 1);
                                tasks[update_index - 1].block = 0;
                            }
                            else if(l == 4){
                                tasks[update_index - 1].block = ((s[0] - '0') * 1);
                                tasks[update_index - 1].blockm = ((s[2] - '0') * 10) + ((s[3] - '0') * 1);
                            }
                            else{
                                tasks[update_index - 1].block = ((s[0] - '0') * 10) + ((s[1] - '0') * 1);
                                tasks[update_index - 1].blockm = ((s[3] - '0') * 10) + ((s[4] - '0') * 1);
                            }

                            if(tasks[update_index - 1].blockm > 59){
                                tasks[update_index - 1].block += tasks[update_index - 1].blockm / 60;
                                tasks[update_index - 1].blockm = tasks[update_index - 1].blockm % 60;
                            }


                            clear_console();
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf(" --------------------\n");
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf("| task block updated |\n");
                            for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                            printf(" --------------------\n\n");
                            break;
                        case 3:
                            clear_console();
                            display_task(update_index);
                            int update_choice;
                            printf("\n ---------------- --------- ------------\n");
                            printf("| 1. In Progress | 2. Done | 3. Dropped |");
                            printf("\n ---------------- --------- ------------\n");
                            printf("| Option: ");
                            scanf("%d", &update_choice);

                            if(update_choice >= 1 && update_choice <= 3){
                                tasks[update_index - 1].status = update_choice;
                                clear_console();
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf(" ---------------------\n");
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf("| task status updated |\n");
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf(" ---------------------\n\n");
                                break;
                            } else{
                                clear_console();
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf(" ---------------------\n");
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf("| invalid task status |\n");
                                for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                                printf(" ---------------------\n\n");
                                break;
                            }
                        case 4:
                            tasks[update_index - 1].status = 0;
                            tasks[update_index - 1].h = 0;
                            tasks[update_index - 1].m = 0;
                            tasks[update_index - 1].s = 0;
                            tasks[update_index - 1].ms = 0;
                            clear_console();
                            for(int i = 0; i < (70 - (11 / 2)); i++) printf(" ");
                            printf(" -------------------\n");
                            for(int i = 0; i < (70 - (11 / 2)); i++) printf(" ");
                            printf("| task time reseted |\n");
                            for(int i = 0; i < (70 - (11 / 2)); i++) printf(" ");
                            printf(" -------------------\n\n");
                            break;
                        default:
                            clear_console();
                            for(int i = 0; i < (70 - (16 / 2)); i++) printf(" ");
                            printf(" -----------------------\n");
                            for(int i = 0; i < (70 - (16 / 2)); i++) printf(" ");
                            printf("| invalid update choice |\n");
                            for(int i = 0; i < (70 - (16 / 2)); i++) printf(" ");
                            printf(" -----------------------\n\n");
                            break;
                    }
                } else {
                    clear_console();
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" -------------------- \n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf("| invalid task index |\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" -------------------- \n\n");
                }
                break;
            case 4:
                if (task_count == 0) {
                    clear_console();
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf("| there are no tasks |\n");
                    for(int i = 0; i < (70 - (12 / 2)); i++) printf(" ");
                    printf(" --------------------\n\n");
                    break;
                }
                clear_console();
                int delete_choice;
                display_tasks(task_count);
                printf("\n -------------------- ---------------------\n");
                  printf("| 1. Delete by Index | 2. Delete All Tasks |");
                  printf("\n -------------------- ---------------------");
                printf("\n| Option: ");
                scanf("%d", &delete_choice);
                if (delete_choice == 1) {
                    clear_console();
                    int delete_index;
                    display_tasks(task_count);
                    printf("| Task Index: ");
                    scanf("%d", &delete_index);
                    delete_index -= 1;
                    if (delete_index >= 0 && delete_index < task_count) {
                        for (int i = delete_index; i < task_count - 1; i++) {
                            strcpy(tasks[i].title, tasks[i + 1].title);
                            tasks[i].block = tasks[i + 1].block;
                            tasks[i].h = tasks[i + 1].h;
                            tasks[i].m = tasks[i + 1].m;
                            tasks[i].s = tasks[i + 1].s;
                            tasks[i].ms = tasks[i + 1].ms;
                            tasks[i].status = tasks[i + 1].status;
                        }
                        task_count--;
                        clear_console();
                        printf("                                                             ---------------------------\n");
                        printf("                                                            | task deleted successfully |\n");
                        printf("                                                             ---------------------------\n\n");
                    } else {
                        clear_console();
                        printf("                                                                       --------------------\n");
                        printf("                                                                      | invalid task index |\n");
                        printf("                                                                       --------------------\n\n");
                    }
                } else if (delete_choice == 2) {
                    task_count = 0;
                    clear_console();
                    for(int i = 0; i < (70 - (9 / 2)); i++) printf(" ");
                    printf("-------------------\n");
                    for(int i = 0; i < (70 - (11 / 2)); i++) printf(" ");
                    printf("| all tasks deleted |\n");
                    for(int i = 0; i < (70 - (9 / 2)); i++) printf(" ");
                    printf("-------------------\n\n");
                } else {
                    clear_console();
                    for(int i = 0; i < (70 - (13 / 2)); i++) printf(" ");
                    printf("-----------------------\n");
                    for(int i = 0; i < (70 - (15 / 2)); i++) printf(" ");
                    printf("| invalid delete choice |\n");
                    for(int i = 0; i < (70 - (15 / 2)); i++) printf(" ");
                    printf("-----------------------\n\n");
                }
                break;
            case 5:
                clear_console();
                system(CLEAR_SCREEN);
                exit(0);
            default:
                clear_console();
                for(int i = 0; i < (70 - (6 / 2)); i++) printf(" ");
                printf("----------------\n");
                for(int i = 0; i < (70 - (8 / 2)); i++) printf(" ");
                printf("| invalid option |\n");
                for(int i = 0; i < (70 - (6 / 2)); i++) printf(" ");
                printf("----------------\n\n");
                break;
        }
    }
    return 0;
}

// Solution to advent of code, day 6

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Part 1
bool lights[1000][1000] = {false};

// Part 2
int dimmable_lights[1000][1000] = {0};

// Checks if the light at (x, y) is within the limits {x0, y0, xend, yend}
bool is_in_range(int x, int y, int* limits)
{
    return (x >= limits[0]) && (x <= limits[2]) && (y >= limits[1]) && (y <= limits[3]);
}

// "482,293" -> {482, 293}
int* str_to_int_pair(char* pair_desc)
{
    static int result[] = {0, 0};

    // This will store one of the two numbers
    char* temp_substring = calloc(4, sizeof(char));

    // Will store the non-numeric part while converting char* to int. Not needed
    char* str_part;
    int pos = 0;

    // Copy everything before the comma in pair_desc to temp_substring
    for(; pair_desc[pos] != ','; pos++)
    {
        temp_substring[pos] = pair_desc[pos];
    }

    // Convert to int and store in result array
    result[0] = (int) strtol(temp_substring, &str_part, 10);

    // Skip the comma
    pos++;

    // Save the position where the second number starts
    int start_of_second_int = pos;

    // Clear the substring that stores one number
    memset(temp_substring, '\0', sizeof(temp_substring)/sizeof(char));

    // Copy everything after the comma in pair_desc to temp_substring
    for(; pair_desc[pos] != '\0'; pos++)
    {
        temp_substring[pos - start_of_second_int] = pair_desc[pos];
    }

    // Convert the second one to int too
    result[1] = (int) strtol(temp_substring, &str_part, 10);

    return result;
}


// "1,2 through 3,4" -> {1, 2, 3, 4}
int* decode_range(char* desc)
{
    int* results = calloc(4, sizeof(int));

    int pos = 0;
    char* tmp_desc = calloc(8, sizeof(char)); // 2 * 3-digit number + ',' + '\0'

    for(; desc[pos] != ' '; pos++)
    {
        tmp_desc[pos] = desc[pos];
    }

    // Convert to int[] and copy to first half of results
    int* start = str_to_int_pair(tmp_desc);
    memcpy(results, start, 2 * sizeof(int));

    // Skip over " through " until we have numbers again
    while (!isdigit(desc[pos]))
    {
        pos++;
    }

    int start_of_second_pair = pos;
    for(; desc[pos] != '\0'; pos++)
    {
        tmp_desc[pos - start_of_second_pair] = desc[pos];
    }

    // Convert to int[] and copy to second half of results
    int* end = str_to_int_pair(tmp_desc);
    memcpy(&(results[2]), start, 2 * sizeof(int));

    return results;
}

// Used for debugging
void print_area(int* area)
{
    // printf("%d,%d to %d,%d\n", area[0], area[1], area[2], area[3]);
    return;
}

void toggle(char* desc)
{
    int* area = decode_range(desc);
    print_area(area);

    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            if (is_in_range(x, y, area))
            {
                lights[x][y] = !lights[x][y];
                dimmable_lights[x][y] += 2;
            }
        }
    }

}

void on(char* desc)
{
    int* area = decode_range(desc);
    print_area(area);

    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            if (is_in_range(x, y, area))
            {
                lights[x][y] = true;
                dimmable_lights[x][y] += 1;
            }
        }
    }
}

void off(char* desc)
{
    int* area = decode_range(desc);
    print_area(area);

    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            if (is_in_range(x, y, area))
            {
                lights[x][y] = false;
                if (dimmable_lights[x][y] > 0)
                {
                    dimmable_lights[x][y] -= 1;
                }
            }
        }
    }
}

void parse_cmd(char* command)
{
    switch (command[6])
    {
        case ' ':
            toggle(command + 7);
            break;
        case 'n':
            on(command + 8);
            break;
        case 'f':
            off(command + 9);
            break;
    }
}

int count_lights_on()
{
    static int lights_on = 0;

    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            if (lights[x][y])
            {
                lights_on++;
            }
        }
    }
    return lights_on;
}

int total_brightness()
{
    static int brightness = 0;

    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            brightness += dimmable_lights[x][y];
        }
    }

    return brightness;
}

int main(int argc, char** argv)
{

    FILE* inputFile = fopen("input6.txt", "r");
    char line[64];

    while(fgets(line, sizeof(line), inputFile))
    {
        parse_cmd(line);
    }

    printf("Part 1: %d lights are on.\n", count_lights_on());

    printf("Part 2: Total brightness is %d.\n", total_brightness());

    return 0;
}

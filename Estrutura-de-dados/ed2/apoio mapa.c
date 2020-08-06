#include <stdio.h>
#include <string.h>

void process_field(int field_count, char *value) {
    if (field_count == 0) {
        printf("Segment:\t");
    }
    if (field_count == 1) {
        printf("Country:\t");
    }
    if (field_count == 2) {
            printf("Product:\t");
    }
    if (field_count == 3) {
        printf("Discound band:\t");
    }
    if (field_count == 4) {
        printf("Units sold:\t");
    }
    if (field_count == 5) {
        printf("Manufacturing price:\t");
    }
    if (field_count == 6) {
        printf("Sale price:\t");
    }
    if (field_count == 7) {
        printf("Gross sales:\t");
    }
    if (field_count == 8) {
        printf("Discounts:\t");
    }
    if (field_count == 9) {
        printf("Sales:\t");
    }
    if (field_count == 10) {
        printf("COGS:\t");
    }
    if (field_count == 11) {
        printf("Profit:\t");
    }
    if (field_count == 12) {
        printf("Date:\t");
    }
    if (field_count == 13) {
        printf("Month number:\t");
    }
    if (field_count == 14) {
        printf("Month name:\t");
    }
    if (field_count == 15) {
        printf("Year:\t");
    }
    printf("%s\n", value);
}

int main(void) {
    char buf[1024];
    char token[1024];

    int row_count = 0;
    int field_count = 0;
    int in_double_quotes = 0;
    int token_pos = 0;
    int i = 0;

    FILE *fp = fopen("sample.csv", "r");

    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }


    while (fgets(buf, 1024, fp)) {
        row_count++;

        if (row_count == 1) {
            continue;
        }

        field_count = 0;
        i = 0;
        do {
            token[token_pos++] = buf[i];

            if (!in_double_quotes && (buf[i] == ',' || buf[i] == '\n')) {
                token[token_pos - 1] = 0;
                token_pos = 0;
                process_field(field_count++, token);
            }

            if (buf[i] == '"' && buf[i + 1] != '"') {
                token_pos--;
                in_double_quotes = !in_double_quotes;
            }

            if (buf[i] == '"' && buf[i + 1] == '"')
                i++;

        } while (buf[++i]);

        printf("\n");
    }

    fclose(fp);

    return 0;
}

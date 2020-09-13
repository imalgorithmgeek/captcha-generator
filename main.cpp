#include <bits/stdc++.h>

/* function prototype */
void captcha_generator(char* captcha_string,size_t size_of_string);
bool checkCaptcha(const char* captcha_string, const char* input_string);

/* CAPTCHA - generate and test */
int main(int argc, char* argv[]) {

    /* get the size of captcha string */
    size_t size_of_captcha{9};

    /* declare character array to store captcha_string and input_string */
    char* captcha_string = new char[size_of_captcha];
    char* input_string = new char[size_of_captcha];

    /* generate a captcha_string */
    captcha_generator(captcha_string,size_of_captcha - 1);

    std::cout << "\nCaptcha String: " << captcha_string << std::endl;

    /* get the input_string from the user */
    std::cout << "\nInput String:";
    std::cin >> input_string;


    if (checkCaptcha(captcha_string, input_string)){
        std::cout << "\nHuman" << std::endl;
    } else {
        std::cout << "\nComputer" << std::endl;
    }

    /* de-allocate the heap-memory */
    delete [] captcha_string;
    delete [] input_string;

    return 0;
}

bool checkCaptcha(const char* captcha_string, const char* input_string){
    size_t i{0};

    /* get the length of captcha_string and input_string */
    size_t captcha_length{strlen(captcha_string)};
    size_t input_length{strlen(input_string)};

    if (captcha_length != input_length) {
        return false;
    } else {
        /* check each character of captcha and input string */
        while(i < captcha_length) {
            if(*(input_string + i) != *(captcha_string + i)) {
                return false;
            }
            i++;
        }
        /* if each character of input_string
         * matched exactly with captcha_string */
        return true;
    }
}

/* a function to generate a captcha string */
void captcha_generator(char* captcha_string,size_t size_of_string) {

    /* define a seed value for random_number_generator */
    auto seed{std::chrono::system_clock::now().time_since_epoch().count()};

    /* declare a random_number_generator with a seeded value */
    std::mt19937 random_number_generator(seed);

    /* define an range for random numbers */
    size_t left_limit{0}, right_limit{2};
    std::uniform_int_distribution<size_t> distinct_type(left_limit, right_limit);

    size_t left_upper_case{65}, right_upper_case{90};
    std::uniform_int_distribution<size_t> distinct_upper_case(left_upper_case, right_upper_case);

    size_t left_lower_case{97}, right_lower_case{122};
    std::uniform_int_distribution<size_t> distinct_lower_case(left_lower_case, right_lower_case);

    size_t left_digit{48}, right_digit{57};
    std::uniform_int_distribution<size_t> distinct_digit(left_digit, right_digit);

    for (size_t i{0};i < size_of_string;i++) {

        /* generate a random character type */
        size_t current_character_type{distinct_type(random_number_generator)};

        switch(current_character_type){
            /* upper-case letters */
            case 0: {

                char character = (char)(distinct_upper_case(random_number_generator));
                captcha_string[i] = character;
                break;
            }
                /* lower-case letters */
            case 1: {
                char character = (char)(distinct_lower_case(random_number_generator));
                captcha_string[i] = character;
                break;
            }
                /* digits */
            case 2: {
                char character = (char)(distinct_digit(random_number_generator));
                captcha_string[i] = character;
                break;
            }
            default: {
                std::cout << "Invalid CAPTCHA!\n" << std::endl;
                break;
            }
        }
    }

    /* NULL terminated array of characters */
    captcha_string[size_of_string] = '\0';
}
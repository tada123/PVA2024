
#include <LT/hh/ltbase.hh>
#include <LT/hh/lt_argparse.hpp>

typedef struct Args{
    LString output;
    LStringList input_fls;
};
void help(){
    puts(
        "1 - Is used for "
        "Usage:"
        "    ..."
    );
    exit(1);
}
size_t set_switch_arg(int argc, char** argv, int current_arg, size_t current_letter, void* opaque){
    Args* s = (Args*) opaque;
    char ch = argv[current_arg][current_letter];
    switch(ch){
        case 'o':
            //Output file
            NEXT_ARG(); //Move to next argument
            s->output = argv[current_arg];
            return 1; //Move 1 arg forward
        case 'h':
            help(); //Should call exit
            return 0;
        default:
            fprintf(stderr, "ERROR: Invalid switch: %c\n", ch);
            exit(1);
    }
    return 0;
}
size_t set_verb_arg(int argc, char** argv, int current_arg, void* opaque){
    Args* s = (Args*) opaque;
    s->input_fls.push(argv[current_arg]);
    return 0;
}

int main(int argc, char** argv){
    if((argc < 2) || (strcmp(argv[1], "--help") == 0)){
        help();
    }

    Args args;
    argparse(argc, argv, &set_switch_arg, &set_verb_arg, &args);
    //Main program starts here

}



comment_c:
/*!re2c
    "*/" {
        goto std;
    }
            
    $ {
        fprintf(stderr, "\nERROR : unterminated comment\n");
        exit(1);
    }

    end {
        fprintf(stderr, "\nERROR : unterminated comment\n");
        exit(1);
    }

    * {
        goto comment_c;
    }
*/


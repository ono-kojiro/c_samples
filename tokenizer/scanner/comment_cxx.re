comment_cxx :
/*!re2c
    $ {
        fprintf(stderr, "\nERROR : unterminated comment\n");
        exit(1);
    }
			
    eol {
        fprintf(s->out, "(EOL)\n");
        goto std;
    }

    end {
        goto std;
    }

    * {
        goto comment_cxx;
    }
*/


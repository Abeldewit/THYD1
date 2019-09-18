#include "hlexer.h"

bool HLexer::remove_whitespaces()
{
    if ( isspace( c_ ) ) {
        for ( ; !c_eoi() && isspace( c_ ); c_next() );
        return true;
    }
    else { return false; }
}


bool HLexer::remove_comment( Token& token ) //TODO do we need this parameter... never used!
{

    bool hasEnded = false;

    // handle the two comment types separately but mutual end of function an exception of needed.
    if(c_ == '{') {

        while (!c_eoi()) {
            c_next();

            if (c_ == '}') {
                hasEnded = true;
                break;
            }
        }
    } else if (c_ == '(') {

        if(c_peek() != '*') {
            // not a comment, just (
            return false;
        }

        // we have an * ==> consume two chars
        c_next();
        c_next();

        // inside a (*  *) comment = look for closing chars
        while (!c_eoi()) {

            if (c_ == '*') {
                if ( c_peek() == ')') {
                    c_next();
                    hasEnded = true;
                    break;
                }
            }
            c_next();
        }

    }
    else {
        // not even a comment in the first place
        return false;
    }

    if(hasEnded) {
        c_next();
        return true;
    }
    else {
        throw LexerException( token.loc, "Unexpected end of comment" );
    }
}


void HLexer::process_string( Token& token )
{
    assert( c_ == '\'' );

    bool has_ended = false;

    while (!c_eoi()) {
        token.text.push_back(c_);
        c_next();
        if (c_ == '\'') {
            has_ended = true;
            break;
        }

        // strings in TP can't span multiple lines
        if(c_ == '\n') {
            break;
        }
    }

    if (!has_ended) {
        throw LexerException( token.loc, "Unexpected end of string" );
    }
    token.text.push_back(c_);
    token.name = LNG::TN::t_string_l;
    c_next();
}


// Process identifier names.
void HLexer::process_identifier( Token& token )
{

    token.text.push_back(c_);
    token.name = LNG::TN::t_identifier;
    c_next();

    while(!c_eoi() && letter_or_digit(c_)) {
        token.text.push_back(c_);
        c_next();
    }
}


// A sequence of numbers/digits e.g. 12345
void HLexer::process_digits( Token& token )
{
    token.text.push_back( c_);
    c_next();

    while( !c_eoi() && digit( c_ )) {
        token.text.push_back( c_);
        c_next();
    }
}


// Process integers and real numbers.
void HLexer::process_number( Token& token )
{
    // We process the first digits
    process_digits(token);
    // And say this is an integer
    token.name = LNG::TN::t_integer;

    // If a period follows...
    if ( c_ == '.') {
        // And the next is a digit
        if ( digit(c_peek()) ) {
            // it's a real
            token.name = LNG::TN::t_real;
            // which can have multiple digits after the period
            process_digits(token);
        } else {
            // if we detected the period but there is no digit after it...
            // lets sey its is an int... because changes are that a range will follow
            //token.text.push_back(c_);
            //c_next();
            // we don't know what it is
            //token.name = LNG::TN::t_unknown;
            return;
        }
    }
    // Then if we see an E or e
    if ( c_ == 'E' || c_ == 'e') {
        token.text.push_back( c_);
        c_next();
        // we can have an optional + or -
        if ( c_ == '-' || c_ == '+') { token.text.push_back( c_); c_next(); }
        // and after that we need a digit
        if ( !digit( c_)) {
            // otherwise it's not a valid number
            token.name = LNG::TN::t_unknown;
            return;
        } else {
            token.name = LNG::TN::t_real;
            process_digits(token);
        }
    }
    //   Provided file test/test4.pas could help with the testing.
}


void HLexer::get( Token& token )
{
    // acc. to Yngvi this next line stops repeated printout when lexer is incomplete
    token.name = LNG::TN::t_unknown;
    token.text.clear();

    // NOTE: Add code to remove comments and white-spaces.
    remove_whitespaces();
    remove_comment(token);

    // the location info. can not be read from the lexer class to the token
    // until after witespaces and comments have been processed
    token.loc = loc_;


    // Return EOI if at end of input
    if ( c_eoi() ) {
        token.name = LNG::TN::t_eoi;
        return;
    }

    // Process a token.
    switch ( c_ ) {
        case ':':
            if (is_.peek() == '=') {
                token.text = ":=";
                token.name = LNG::TN::t_assign;
                c_next();
                c_next();
            } else {
                set( token, LNG::TN::t_colon );
            }
            break;
        case '=': set( token, LNG::TN::t_eq );
            break;
        case '/': set( token, LNG::TN::t_divide );
            break;
        case '>':
            if (is_.peek() == '=') {
                token.text =  ">=";
                token.name = LNG::TN::t_gteq;
                c_next();
                c_next();
            }
            else {
                set(token, LNG::TN::t_gt);
            }
            break;
        case '<':
            if (is_.peek() == '=') {
                token.text =  "<=";
                token.name = LNG::TN::t_lteq;
                c_next();
                c_next();
            }
            else if(is_.peek() == '>') {
                token.text =  "<>";
                token.name = LNG::TN::t_neq;
                c_next();
                c_next();
            }
            else {
                set(token, LNG::TN::t_lt);
            }
            break;
        case '-': set( token, LNG::TN::t_minus );
            break;
        case '*': set( token, LNG::TN::t_multiply );
            break;
        case '+': set( token, LNG::TN::t_plus );
            break;
        case '^': set( token, LNG::TN::t_caret );
            break;
        case ',': set( token, LNG::TN::t_comma );
            break;
        case '.':
            if(is_.peek() == '.') {
                token.text = "..";
                token.name = LNG::TN::t_subrange;
                c_next();
                c_next();
            }
            else {
                set(token, LNG::TN::t_dot);
            }
            break;
        case '[': set( token, LNG::TN::t_lbracket );
            break;
        case '(': set( token, LNG::TN::t_lparenthesis );
            break;
        case ']': set( token, LNG::TN::t_rbracket );
            break;
        case ')': set( token, LNG::TN::t_rparenthesis );
            break;
        case ';': set( token, LNG::TN::t_semicolon );
            break;

        default:
            if ( c_ == '\'' )        { process_string( token ); }
            else if ( digit( c_ ) )  { process_number( token ); }
            else if ( letter( c_ ) ) {
                process_identifier( token );
                // the find function returns an iterator to a matching key in the map
                // if not it is pointing to the map's end, as checked in the if thereafter.
                auto it = LNG::ReservedWordToTokenName.find( Common::to_lower( token.text ) );
                if ( it != LNG::ReservedWordToTokenName.end() ) {
                    token.name = it->second;
                }
            }
            else { set( token, LNG::TN::t_unknown ); }
    }
}

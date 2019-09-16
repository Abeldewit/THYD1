#include "hlexer.h"

bool HLexer::remove_whitespaces()
{
    if ( isspace( c_ ) ) {
        for ( ; !c_eoi() && isspace( c_ ); c_next() );
        return true;
    }
    else { return false; }
}


bool HLexer::remove_comment( Token& token )
{
    if(c_ == '{') {
        bool end_of_comment = false;
        bool star_comment = false;

        //token.text.push_back(c_);
        c_next();
        remove_whitespaces();
        if ( c_ == '*') { star_comment = true; }

        while (!c_eoi() && !end_of_comment) {
            //token.text.push_back(c_);
            c_next();
            remove_whitespaces();
            if ( star_comment ) {
                if ( c_ == '*') {
                    //token.text.push_back(c_);
                    c_next();
                    if ( c_ == '}') {
                        end_of_comment = true;
                        c_next();
                        break;
                    }
                }
            } else {
                if (c_ == '}') {
                    end_of_comment = true;
                    c_next();
                    break;
                }
            }
        }
        if (end_of_comment) {
            return true;
        } else {
            return false;
        }
    }

    // TODO: CHECK.. warning: control reaches the end of a non-void function
    return false;
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
    // actually this check below has already been made before calling this function so strictly it is not needed.
    if(isalpha(c_) || c_ == '_') {
        token.text.push_back(c_);
        token.name = LNG::TN::t_identifier;
        c_next();

        // after the && we could just call the letter_or_digit() helper of current class
        while(!c_eoi() && (isalnum(c_) || c_ == '_')) {
            token.text.push_back(c_);
            c_next();
        }
    }
}


// A sequence of numbers/digits e.g. 12345
void HLexer::process_digits( Token& token )
{
    // NOTE: Add your code here (instead of the provided c_next()).
    c_next();
}


// Process integers and real numbers.
void HLexer::process_number( Token& token )
{
    // NOTE: Add your code here (instead of the provided c_next()).
    c_next();
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
                set( token, LNG::TN::t_dot );
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

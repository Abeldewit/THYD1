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
    // NOTE: Add your code here (instead of the provided c_next()).
    c_next();

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
    token.text.clear();
    token.loc = loc_;

    // NOTE: Add code to remove comments and white-spaces.
    remove_whitespaces();
    remove_comment(token);

    // Return EOI if at end of input
    if ( c_eoi() ) {
        token.name = LNG::TN::t_eoi;
        return;
    }

    // Process a token.
    switch ( c_ ) {
        case ';': set( token, LNG::TN::t_semicolon );
            break;
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

         // NOTE: Add code here for all the remaining cases.

        default:
            if ( c_ == '\'' )        { process_string( token ); }
            else if ( digit( c_ ) )  { process_number( token ); }
            else if ( letter( c_ ) ) {
                process_identifier( token );
                auto it = LNG::ReservedWordToTokenName.find( Common::to_lower( token.text ) );
                if ( it != LNG::ReservedWordToTokenName.end() ) {
                    token.name = it->second;
                }
            }
            else { set( token, LNG::TN::t_unknown ); }
    }
}

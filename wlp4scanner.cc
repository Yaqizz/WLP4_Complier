#include <iostream>
#include <vector>

#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <utility>
#include <set>
#include <array>

#include <string>
#include <vector>
#include <set>
#include <cstdint>

class Token {
  public:
    enum Kind {
      ID = 0,
      NUM,
      LPAREN,
      RPAREN,
      LBRACE,
      RBRACE,
      BECOMES,
      EQ,
      NE,
      LT,
      GT,
      LE,
      GE,
      PLUS,
      MINUS,
      STAR,
      SLASH,
      PCT,
      COMMA,
      SEMI,
      LBRACK,
      RBRACK,
      AMP,
      WHITESPACE,
      COMMENT
    };

  private:
    Kind kind;
    std::string lexeme;

  public:
    Token(Kind kind, std::string lexeme);

    Kind getKind() const;
    const std::string &getLexeme() const;
};

/* Prints a string representation of a token.
 * Mainly useful for debugging.
 */
std::ostream &operator<<(std::ostream &out, const Token &tok);

/* An exception class thrown when an error is encountered while scanning.
 */
class ScanningFailure {
    std::string message;

  public:
    ScanningFailure(std::string message):
    message(std::move(message)) {}
    const std::string &what() const { return message; }
};

Token::Token(Token::Kind kind, std::string lexeme):
  kind(kind), lexeme(std::move(lexeme)) {}

  Token:: Kind Token::getKind() const { return kind; }
const std::string &Token::getLexeme() const { return lexeme; }

std::ostream &operator<<(std::ostream &out, const Token &tok) {
  switch (tok.getKind()) {
    case Token::ID:         out << "ID";         break;
    case Token::NUM:        out << "NUM";        break;
    case Token::LPAREN:     out << "LPAREN";     break;
    case Token::RPAREN:     out << "RPAREN";     break;
    case Token::LBRACE:     out << "LBRACE";     break;
    case Token::RBRACE:     out << "RBRACE";     break;
    case Token::BECOMES:    out << "BECOMES";    break;
    case Token::EQ:         out << "EQ";         break;
    case Token::NE:         out << "NE";         break;
    case Token::LT:         out << "LT";         break;
    case Token::GT:         out << "GT";         break;
    case Token::LE:         out << "LE";         break;
    case Token::GE:         out << "GE";         break;
    case Token::PLUS:       out << "PLUS";       break;
    case Token::MINUS:      out << "MINUS";      break;
    case Token::STAR:       out << "STAR";       break;
    case Token::SLASH:      out << "SLASH";      break;
    case Token::PCT:        out << "PCT";        break;
    case Token::COMMA:      out << "COMMA";      break;
    case Token::SEMI:       out << "SEMI";       break;
    case Token::LBRACK:     out << "LBRACK";     break;
    case Token::RBRACK:     out << "RBRACK";     break;
    case Token::AMP:        out << "AMP";        break;
    case Token::WHITESPACE:                      break;
    case Token::COMMENT:                         break;
  }
  out << " " << tok.getLexeme() << std::endl;
  return out;
}

/* Representation of a DFA, used to handle the scanning process.
 */
class AsmDFA {
  public:
    enum State {
      // States that are also kinds
      ID = 0,
      NUM,
      LPAREN,
      RPAREN,
      LBRACE,
      RBRACE,
      BECOMES,
      EQ,
      NE,
      LT,
      GT,
      LE,
      GE,
      PLUS,
      MINUS,
      STAR,
      SLASH,
      PCT,
      COMMA,
      SEMI,
      LBRACK,
      RBRACK,
      AMP,
      WHITESPACE,
      COMMENT,
      ZERO,
      NE_M,

      // States that are not also kinds
      FAIL,
      START,

      // Hack to let this be used easily in arrays. This should always be the
      // final element in the enum, and should always point to the previous
      // element.

      LARGEST_STATE = START
    };

  private:
    /* A set of all accepting states for the DFA.
     * Currently non-accepting states are not actually present anywhere
     * in memory, but a list can be found in the constructor.
     */
    std::set<State> acceptingStates;

    /*
     * The transition function for the DFA, stored as a map.
     */

    std::array<std::array<State, 128>, LARGEST_STATE + 1> transitionFunction;

    /*
     * Converts a state to a kind to allow construction of Tokens from States.
     * Throws an exception if conversion is not possible.
     */
    Token::Kind stateToKind(State s) const {
      switch(s) {
        case ID:         return Token::ID;
        case NUM:        return Token::NUM;
        case LPAREN:     return Token::LPAREN;
        case RPAREN:     return Token::RPAREN;
        case LBRACE:     return Token::LBRACE;
        case RBRACE:     return Token::RBRACE;
        case BECOMES:    return Token::BECOMES;
        case EQ:         return Token::EQ;
        case NE:         return Token::NE;
        case LT:         return Token::LT;
        case GT:         return Token::GT;
        case LE:         return Token::LE;
        case GE:         return Token::GE;
        case PLUS:       return Token::PLUS;
        case MINUS:      return Token::MINUS;
        case STAR:       return Token::STAR;
        case SLASH:      return Token::SLASH;
        case PCT:        return Token::PCT;
        case COMMA:      return Token::COMMA;
        case SEMI:       return Token::SEMI;
        case LBRACK:     return Token::LBRACK;
        case RBRACK:     return Token::RBRACK;
        case AMP:        return Token::AMP;
        case WHITESPACE: return Token::WHITESPACE;
        case COMMENT:    return Token::COMMENT;
        case ZERO:       return Token::NUM;
        default: throw ScanningFailure("ERROR: Cannot convert state to kind.");
      }
    }


  public:
    /* Tokenizes an input string according to the Simplified Maximal Munch
     * scanning algorithm.
     */
    std::vector<Token> simplifiedMaximalMunch(const std::string &input) const {
      std::vector<Token> result;

      State state = start();
      std::string munchedInput;

      // We can't use a range-based for loop effectively here
      // since the iterator doesn't always increment.
      for (std::string::const_iterator inputPosn = input.begin();
           inputPosn != input.end();) {

        State oldState = state;
        state = transition(state, *inputPosn);

        if (!failed(state)) {
          munchedInput += *inputPosn;
          oldState = state;

          ++inputPosn;
        }

        if (inputPosn == input.end() || failed(state)) {
          if (accept(oldState)) {
            result.push_back(Token(stateToKind(oldState), munchedInput));

            munchedInput = "";
            state = start();
          } else {
            if (failed(state)) {
              munchedInput += *inputPosn;
            }
            throw ScanningFailure("ERROR: Simplified maximal munch failed on input: "
                                 + munchedInput);
          }
        }
      }

      return result;
    }

    /* Initializes the accepting states for the DFA.
     */
    AsmDFA() {
      acceptingStates = 
        {ID, NUM, LPAREN, RPAREN, LBRACE, RBRACE, BECOMES, EQ, NE, LT, GT, LE, GE, PLUS, MINUS, STAR, SLASH,
         PCT, COMMA, SEMI, LBRACK, RBRACK, AMP, WHITESPACE, COMMENT, ZERO};
      //Non-accepting states are DOT, MINUS, ZEROX, DOLLARS, START

      // Initialize transitions for the DFA
      for (size_t i = 0; i < transitionFunction.size(); ++i) {
        for (size_t j = 0; j < transitionFunction[0].size(); ++j) {
          transitionFunction[i][j] = FAIL;
        }
      }
      registerTransition(START, isalpha, ID);
      registerTransition(ID, isalnum, ID);
      registerTransition(START, "123456789", NUM);
      registerTransition(START, "0", ZERO);
      registerTransition(NUM, isdigit, NUM);
      registerTransition(START, "(", LPAREN);
      registerTransition(START, ")", RPAREN);
      registerTransition(START, "{", LBRACE);
      registerTransition(START, "}", RBRACE);
      registerTransition(START, "=", BECOMES);
      registerTransition(BECOMES, "=", EQ);
      registerTransition(START, "!", NE_M);
      registerTransition(NE_M, "=", NE);
      registerTransition(START, "<", LT);
      registerTransition(START, ">", GT);
      registerTransition(LT, "=", LE);
      registerTransition(GT, "=", GE);
      registerTransition(START, "+", PLUS);
      registerTransition(START, "-", MINUS);
      registerTransition(START, "*", STAR);
      registerTransition(START, "/", SLASH);
      registerTransition(START, "%", PCT);
      registerTransition(START, ",", COMMA);
      registerTransition(START, ";", SEMI);
      registerTransition(START, "[", LBRACK);
      registerTransition(START, "]", RBRACK);
      registerTransition(START, "&", AMP);

      registerTransition(SLASH, "//", COMMENT);
      registerTransition(START, isspace, WHITESPACE);;
      registerTransition(COMMENT, [](int c) -> int { return c != '\n'; },
          COMMENT);
      registerTransition(WHITESPACE, isspace, WHITESPACE);
    }

    // Register a transition on all chars in chars
    void registerTransition(State oldState, const std::string &chars,
        State newState) {
      for (char c : chars) {
        transitionFunction[oldState][c] = newState;
      }
    }

    // Register a transition on all chars matching test
    // For some reason the cctype functions all use ints, hence the function
    // argument type.
    void registerTransition(State oldState, int (*test)(int), State newState) {

      for (int c = 0; c < 128; ++c) {
        if (test(c)) {
          transitionFunction[oldState][c] = newState;
        }
      }
    }

    State transition(State state, char nextChar) const {
      return transitionFunction[state][nextChar];
    }

    bool failed(State state) const { return state == FAIL; }

    bool accept(State state) const {
      return acceptingStates.count(state) > 0;
    }

    /* Returns the starting state of the DFA
     */
    State start() const { return START; }
};

std::vector<Token> scan(const std::string &input) {
  static AsmDFA theDFA;

  std::vector<Token> tokens = theDFA.simplifiedMaximalMunch(input);

  std::vector<Token> newTokens;

  for (auto &token : tokens) {
    if (token.getKind() != Token::WHITESPACE
        && token.getKind() != Token::Kind::COMMENT) {
      newTokens.push_back(token);
    }
  }

  return newTokens;
}

// true if a > b
bool compare(std::string a, std::string b) {
  int an = a.length();
  int bn = b.length();
  if (an > bn) {
    return true;
  } else if (an < bn) {
    return false;
  } else {
    for (int i = 0; i < an; i++) {
      if ((a[i] - '0') < (b[i] - '0')) { 
        return false;
      }
    }
    return true;
  }
}


int main() {
  std::string line;
  try {
    while (getline(std::cin, line)) {
      std::vector<Token> tokenLine = scan(line);
      int n = tokenLine.size();
      for (int i = 0; i < n; i++) {
        switch (tokenLine[i].getKind()) {
          case Token::ID: {
            // check name
            std::string lex = tokenLine[i].getLexeme();
            if (lex != "wain" && lex != "int" && lex != "if" && lex != "else" && lex != "while" && 
                lex != "println" && lex != "return" && lex != "NULL" && lex != "new" && lex != "delete") {
              std::cout << tokenLine[i];
            } else if (lex == "wain") {
              std::cout << "WAIN wain" << std::endl;
            } else if (lex == "int") {
              std::cout << "INT int" << std::endl;
            } else if (lex == "if") {
              std::cout << "IF if" << std::endl;
            } else if (lex == "else") {
              std::cout << "ELSE else" << std::endl;
            } else if (lex == "while") {
              std::cout << "WHILE while" << std::endl;
            } else if (lex == "println") {
              std::cout << "PRINTLN println" << std::endl;
            } else if (lex == "return") {
              std::cout << "RETURN return" << std::endl;
            } else if (lex == "NULL") {
              std::cout << "NULL NULL" << std::endl;
            } else if (lex == "new") {
              std::cout << "NEW new" << std::endl;
            } else if (lex == "delete") {
              std::cout << "DELETE delete" << std::endl;
            }
            break;
          }
          case Token::NUM: {
            // check range
            std::string lex = tokenLine[i].getLexeme();
            std::string max = "2147483647";
            if (compare(lex, max)) {
              std::cerr << lex << std::endl;
              throw ScanningFailure("ERROR: OUT OF RANGE");
            } else {
              std::cout << tokenLine[i];
            }
            break;
          } 
          default: std::cout << tokenLine[i]; break;
        }
      }
    }
  } catch (ScanningFailure &f) {
    std::cerr << f.what() << std::endl;
    return 1;
  }
  return 0;
}

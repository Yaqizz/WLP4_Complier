#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>


#include<string>
const std::string WLP4_CFG = R"END(.CFG
start BOF procedures EOF
procedures procedure procedures
procedures main
procedure INT ID LPAREN params RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE
main INT WAIN LPAREN dcl COMMA dcl RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE
params .EMPTY
params paramlist
paramlist dcl
paramlist dcl COMMA paramlist
type INT
type INT STAR
dcls .EMPTY
dcls dcls dcl BECOMES NUM SEMI
dcls dcls dcl BECOMES NULL SEMI
dcl type ID
statements .EMPTY
statements statements statement
statement lvalue BECOMES expr SEMI
statement IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
statement WHILE LPAREN test RPAREN LBRACE statements RBRACE
statement PRINTLN LPAREN expr RPAREN SEMI
statement DELETE LBRACK RBRACK expr SEMI
test expr EQ expr
test expr NE expr
test expr LT expr
test expr LE expr
test expr GE expr
test expr GT expr
expr term
expr expr PLUS term
expr expr MINUS term
term factor
term term STAR factor
term term SLASH factor
term term PCT factor
factor ID
factor NUM
factor NULL
factor LPAREN expr RPAREN
factor AMP lvalue
factor STAR factor
factor NEW INT LBRACK expr RBRACK
factor ID LPAREN RPAREN
factor ID LPAREN arglist RPAREN
arglist expr
arglist expr COMMA arglist
lvalue ID
lvalue STAR factor
lvalue LPAREN lvalue RPAREN
)END";

const std::string WLP4_TRANSITIONS = R"END(.TRANSITIONS
0 BOF 45
1 AMP 35
1 ID 13
1 LPAREN 1
1 NEW 30
1 NULL 33
1 NUM 10
1 STAR 6
1 expr 86
1 factor 83
1 term 51
100 EQ 40
100 GE 37
100 GT 46
100 LE 34
100 LT 27
100 MINUS 3
100 NE 14
100 PLUS 74
102 AMP 35
102 ID 13
102 LPAREN 1
102 NEW 30
102 NULL 33
102 NUM 10
102 STAR 6
102 expr 11
102 factor 83
102 term 51
103 AMP 35
103 ID 13
103 LPAREN 1
103 NEW 30
103 NULL 33
103 NUM 10
103 RPAREN 44
103 STAR 6
103 arglist 125
103 expr 38
103 factor 83
103 term 51
104 AMP 35
104 ID 13
104 LPAREN 1
104 NEW 30
104 NULL 33
104 NUM 10
104 STAR 6
104 expr 72
104 factor 83
104 term 51
105 AMP 35
105 ID 13
105 LPAREN 1
105 NEW 30
105 NULL 33
105 NUM 10
105 STAR 6
105 factor 55
108 DELETE 57
108 ID 19
108 IF 53
108 LPAREN 4
108 PRINTLN 2
108 RBRACE 119
108 STAR 73
108 WHILE 43
108 lvalue 12
108 statement 20
109 DELETE 57
109 ID 19
109 IF 53
109 LPAREN 4
109 PRINTLN 2
109 RBRACE 120
109 STAR 73
109 WHILE 43
109 lvalue 12
109 statement 20
11 MINUS 3
11 PLUS 74
11 SEMI 23
110 DELETE 57
110 ID 19
110 IF 53
110 LPAREN 4
110 PRINTLN 2
110 RBRACE 121
110 STAR 73
110 WHILE 43
110 lvalue 12
110 statement 20
111 AMP 35
111 ID 13
111 LPAREN 1
111 NEW 30
111 NULL 33
111 NUM 10
111 STAR 6
111 factor 54
113 LBRACE 77
114 SEMI 69
115 INT 68
115 main 28
115 procedure 115
115 procedures 16
118 AMP 35
118 ID 13
118 LPAREN 1
118 NEW 30
118 NULL 33
118 NUM 10
118 STAR 6
118 arglist 65
118 expr 38
118 factor 83
118 term 51
119 ELSE 113
12 BECOMES 97
122 INT 17
122 dcl 15
122 paramlist 123
122 params 18
122 type 48
124 INT 17
124 dcl 63
124 statements 42
124 type 48
125 RPAREN 24
126 LBRACK 79
128 LPAREN 84
129 EOF 107
13 LPAREN 103
131 LPAREN 122
14 AMP 35
14 ID 13
14 LPAREN 1
14 NEW 30
14 NULL 33
14 NUM 10
14 STAR 6
14 expr 88
14 factor 83
14 term 51
15 COMMA 99
17 STAR 95
18 RPAREN 36
2 LPAREN 9
23 RBRACE 41
25 LBRACE 61
27 AMP 35
27 ID 13
27 LPAREN 1
27 NEW 30
27 NULL 33
27 NUM 10
27 STAR 6
27 expr 89
27 factor 83
27 term 51
29 DELETE 57
29 ID 19
29 IF 53
29 LPAREN 4
29 PRINTLN 2
29 RETURN 102
29 STAR 73
29 WHILE 43
29 lvalue 12
29 statement 20
3 AMP 35
3 ID 13
3 LPAREN 1
3 NEW 30
3 NULL 33
3 NUM 10
3 STAR 6
3 factor 83
3 term 60
30 INT 126
31 LBRACE 80
32 LBRACE 81
34 AMP 35
34 ID 13
34 LPAREN 1
34 NEW 30
34 NULL 33
34 NUM 10
34 STAR 6
34 expr 90
34 factor 83
34 term 51
35 ID 19
35 LPAREN 4
35 STAR 73
35 lvalue 93
36 LBRACE 5
37 AMP 35
37 ID 13
37 LPAREN 1
37 NEW 30
37 NULL 33
37 NUM 10
37 STAR 6
37 expr 91
37 factor 83
37 term 51
38 COMMA 118
38 MINUS 3
38 PLUS 74
39 RBRACE 106
4 ID 19
4 LPAREN 4
4 STAR 73
4 lvalue 94
40 AMP 35
40 ID 13
40 LPAREN 1
40 NEW 30
40 NULL 33
40 NUM 10
40 STAR 6
40 expr 87
40 factor 83
40 term 51
42 DELETE 57
42 ID 19
42 IF 53
42 LPAREN 4
42 PRINTLN 2
42 RETURN 52
42 STAR 73
42 WHILE 43
42 lvalue 12
42 statement 20
43 LPAREN 8
45 INT 68
45 main 28
45 procedure 115
45 procedures 129
46 AMP 35
46 ID 13
46 LPAREN 1
46 NEW 30
46 NULL 33
46 NUM 10
46 STAR 6
46 expr 92
46 factor 83
46 term 51
48 ID 101
49 RPAREN 31
5 dcls 98
50 RPAREN 32
51 PCT 67
51 SLASH 105
51 STAR 111
52 AMP 35
52 ID 13
52 LPAREN 1
52 NEW 30
52 NULL 33
52 NUM 10
52 STAR 6
52 expr 64
52 factor 83
52 term 51
53 LPAREN 7
57 LBRACK 78
58 SEMI 117
59 PCT 67
59 SLASH 105
59 STAR 111
6 AMP 35
6 ID 13
6 LPAREN 1
6 NEW 30
6 NULL 33
6 NUM 10
6 STAR 6
6 factor 26
60 PCT 67
60 SLASH 105
60 STAR 111
61 dcls 124
62 NULL 58
62 NUM 82
63 BECOMES 62
64 MINUS 3
64 PLUS 74
64 SEMI 39
67 AMP 35
67 ID 13
67 LPAREN 1
67 NEW 30
67 NULL 33
67 NUM 10
67 STAR 6
67 factor 56
68 ID 131
68 WAIN 128
7 AMP 35
7 ID 13
7 LPAREN 1
7 NEW 30
7 NULL 33
7 NUM 10
7 STAR 6
7 expr 100
7 factor 83
7 term 51
7 test 49
70 MINUS 3
70 PLUS 74
70 SEMI 22
71 MINUS 3
71 PLUS 74
71 RPAREN 114
72 MINUS 3
72 PLUS 74
72 SEMI 21
73 AMP 35
73 ID 13
73 LPAREN 1
73 NEW 30
73 NULL 33
73 NUM 10
73 STAR 6
73 factor 66
74 AMP 35
74 ID 13
74 LPAREN 1
74 NEW 30
74 NULL 33
74 NUM 10
74 STAR 6
74 factor 83
74 term 59
75 COMMA 96
76 RPAREN 25
77 statements 110
78 RBRACK 104
79 AMP 35
79 ID 13
79 LPAREN 1
79 NEW 30
79 NULL 33
79 NUM 10
79 STAR 6
79 expr 85
79 factor 83
79 term 51
8 AMP 35
8 ID 13
8 LPAREN 1
8 NEW 30
8 NULL 33
8 NUM 10
8 STAR 6
8 expr 100
8 factor 83
8 term 51
8 test 50
80 statements 108
81 statements 109
82 SEMI 116
84 INT 17
84 dcl 75
84 type 48
85 MINUS 3
85 PLUS 74
85 RBRACK 47
86 MINUS 3
86 PLUS 74
86 RPAREN 112
87 MINUS 3
87 PLUS 74
88 MINUS 3
88 PLUS 74
89 MINUS 3
89 PLUS 74
9 AMP 35
9 ID 13
9 LPAREN 1
9 NEW 30
9 NULL 33
9 NUM 10
9 STAR 6
9 expr 71
9 factor 83
9 term 51
90 MINUS 3
90 PLUS 74
91 MINUS 3
91 PLUS 74
92 MINUS 3
92 PLUS 74
94 RPAREN 130
96 INT 17
96 dcl 76
96 type 48
97 AMP 35
97 ID 13
97 LPAREN 1
97 NEW 30
97 NULL 33
97 NUM 10
97 STAR 6
97 expr 70
97 factor 83
97 term 51
98 INT 17
98 dcl 63
98 statements 29
98 type 48
99 INT 17
99 dcl 15
99 paramlist 127
99 type 48
)END";

const std::string WLP4_REDUCTIONS = R"END(.REDUCTIONS
10 36 BECOMES
10 36 COMMA
10 36 EQ
10 36 GE
10 36 GT
10 36 LE
10 36 LT
10 36 MINUS
10 36 NE
10 36 PCT
10 36 PLUS
10 36 RBRACK
10 36 RPAREN
10 36 SEMI
10 36 SLASH
10 36 STAR
101 14 BECOMES
101 14 COMMA
101 14 RPAREN
106 4 EOF
107 0 .ACCEPT
112 38 BECOMES
112 38 COMMA
112 38 EQ
112 38 GE
112 38 GT
112 38 LE
112 38 LT
112 38 MINUS
112 38 NE
112 38 PCT
112 38 PLUS
112 38 RBRACK
112 38 RPAREN
112 38 SEMI
112 38 SLASH
112 38 STAR
116 12 DELETE
116 12 ID
116 12 IF
116 12 INT
116 12 LPAREN
116 12 PRINTLN
116 12 RETURN
116 12 STAR
116 12 WHILE
117 13 DELETE
117 13 ID
117 13 IF
117 13 INT
117 13 LPAREN
117 13 PRINTLN
117 13 RETURN
117 13 STAR
117 13 WHILE
120 19 DELETE
120 19 ID
120 19 IF
120 19 LPAREN
120 19 PRINTLN
120 19 RBRACE
120 19 RETURN
120 19 STAR
120 19 WHILE
121 18 DELETE
121 18 ID
121 18 IF
121 18 LPAREN
121 18 PRINTLN
121 18 RBRACE
121 18 RETURN
121 18 STAR
121 18 WHILE
122 5 RPAREN
123 6 RPAREN
124 15 DELETE
124 15 ID
124 15 IF
124 15 LPAREN
124 15 PRINTLN
124 15 RBRACE
124 15 RETURN
124 15 STAR
124 15 WHILE
127 8 RPAREN
13 35 BECOMES
13 35 COMMA
13 35 EQ
13 35 GE
13 35 GT
13 35 LE
13 35 LT
13 35 MINUS
13 35 NE
13 35 PCT
13 35 PLUS
13 35 RBRACK
13 35 RPAREN
13 35 SEMI
13 35 SLASH
13 35 STAR
130 48 BECOMES
130 48 COMMA
130 48 EQ
130 48 GE
130 48 GT
130 48 LE
130 48 LT
130 48 MINUS
130 48 NE
130 48 PCT
130 48 PLUS
130 48 RBRACK
130 48 RPAREN
130 48 SEMI
130 48 SLASH
130 48 STAR
15 7 RPAREN
16 1 EOF
17 9 ID
19 46 BECOMES
19 46 COMMA
19 46 EQ
19 46 GE
19 46 GT
19 46 LE
19 46 LT
19 46 MINUS
19 46 NE
19 46 PCT
19 46 PLUS
19 46 RBRACK
19 46 RPAREN
19 46 SEMI
19 46 SLASH
19 46 STAR
20 16 DELETE
20 16 ID
20 16 IF
20 16 LPAREN
20 16 PRINTLN
20 16 RBRACE
20 16 RETURN
20 16 STAR
20 16 WHILE
21 21 DELETE
21 21 ID
21 21 IF
21 21 LPAREN
21 21 PRINTLN
21 21 RBRACE
21 21 RETURN
21 21 STAR
21 21 WHILE
22 17 DELETE
22 17 ID
22 17 IF
22 17 LPAREN
22 17 PRINTLN
22 17 RBRACE
22 17 RETURN
22 17 STAR
22 17 WHILE
24 43 BECOMES
24 43 COMMA
24 43 EQ
24 43 GE
24 43 GT
24 43 LE
24 43 LT
24 43 MINUS
24 43 NE
24 43 PCT
24 43 PLUS
24 43 RBRACK
24 43 RPAREN
24 43 SEMI
24 43 SLASH
24 43 STAR
26 40 BECOMES
26 40 COMMA
26 40 EQ
26 40 GE
26 40 GT
26 40 LE
26 40 LT
26 40 MINUS
26 40 NE
26 40 PCT
26 40 PLUS
26 40 RBRACK
26 40 RPAREN
26 40 SEMI
26 40 SLASH
26 40 STAR
28 2 EOF
33 37 BECOMES
33 37 COMMA
33 37 EQ
33 37 GE
33 37 GT
33 37 LE
33 37 LT
33 37 MINUS
33 37 NE
33 37 PCT
33 37 PLUS
33 37 RBRACK
33 37 RPAREN
33 37 SEMI
33 37 SLASH
33 37 STAR
38 44 RPAREN
41 3 INT
44 42 BECOMES
44 42 COMMA
44 42 EQ
44 42 GE
44 42 GT
44 42 LE
44 42 LT
44 42 MINUS
44 42 NE
44 42 PCT
44 42 PLUS
44 42 RBRACK
44 42 RPAREN
44 42 SEMI
44 42 SLASH
44 42 STAR
47 41 BECOMES
47 41 COMMA
47 41 EQ
47 41 GE
47 41 GT
47 41 LE
47 41 LT
47 41 MINUS
47 41 NE
47 41 PCT
47 41 PLUS
47 41 RBRACK
47 41 RPAREN
47 41 SEMI
47 41 SLASH
47 41 STAR
5 11 DELETE
5 11 ID
5 11 IF
5 11 INT
5 11 LPAREN
5 11 PRINTLN
5 11 RETURN
5 11 STAR
5 11 WHILE
51 28 COMMA
51 28 EQ
51 28 GE
51 28 GT
51 28 LE
51 28 LT
51 28 MINUS
51 28 NE
51 28 PLUS
51 28 RBRACK
51 28 RPAREN
51 28 SEMI
54 32 COMMA
54 32 EQ
54 32 GE
54 32 GT
54 32 LE
54 32 LT
54 32 MINUS
54 32 NE
54 32 PCT
54 32 PLUS
54 32 RBRACK
54 32 RPAREN
54 32 SEMI
54 32 SLASH
54 32 STAR
55 33 COMMA
55 33 EQ
55 33 GE
55 33 GT
55 33 LE
55 33 LT
55 33 MINUS
55 33 NE
55 33 PCT
55 33 PLUS
55 33 RBRACK
55 33 RPAREN
55 33 SEMI
55 33 SLASH
55 33 STAR
56 34 COMMA
56 34 EQ
56 34 GE
56 34 GT
56 34 LE
56 34 LT
56 34 MINUS
56 34 NE
56 34 PCT
56 34 PLUS
56 34 RBRACK
56 34 RPAREN
56 34 SEMI
56 34 SLASH
56 34 STAR
59 29 COMMA
59 29 EQ
59 29 GE
59 29 GT
59 29 LE
59 29 LT
59 29 MINUS
59 29 NE
59 29 PLUS
59 29 RBRACK
59 29 RPAREN
59 29 SEMI
60 30 COMMA
60 30 EQ
60 30 GE
60 30 GT
60 30 LE
60 30 LT
60 30 MINUS
60 30 NE
60 30 PLUS
60 30 RBRACK
60 30 RPAREN
60 30 SEMI
61 11 DELETE
61 11 ID
61 11 IF
61 11 INT
61 11 LPAREN
61 11 PRINTLN
61 11 RETURN
61 11 STAR
61 11 WHILE
65 45 RPAREN
66 47 BECOMES
66 47 COMMA
66 47 EQ
66 47 GE
66 47 GT
66 47 LE
66 47 LT
66 47 MINUS
66 47 NE
66 47 PCT
66 47 PLUS
66 47 RBRACK
66 47 RPAREN
66 47 SEMI
66 47 SLASH
66 47 STAR
69 20 DELETE
69 20 ID
69 20 IF
69 20 LPAREN
69 20 PRINTLN
69 20 RBRACE
69 20 RETURN
69 20 STAR
69 20 WHILE
77 15 DELETE
77 15 ID
77 15 IF
77 15 LPAREN
77 15 PRINTLN
77 15 RBRACE
77 15 RETURN
77 15 STAR
77 15 WHILE
80 15 DELETE
80 15 ID
80 15 IF
80 15 LPAREN
80 15 PRINTLN
80 15 RBRACE
80 15 RETURN
80 15 STAR
80 15 WHILE
81 15 DELETE
81 15 ID
81 15 IF
81 15 LPAREN
81 15 PRINTLN
81 15 RBRACE
81 15 RETURN
81 15 STAR
81 15 WHILE
83 31 COMMA
83 31 EQ
83 31 GE
83 31 GT
83 31 LE
83 31 LT
83 31 MINUS
83 31 NE
83 31 PCT
83 31 PLUS
83 31 RBRACK
83 31 RPAREN
83 31 SEMI
83 31 SLASH
83 31 STAR
87 22 RPAREN
88 23 RPAREN
89 24 RPAREN
90 25 RPAREN
91 26 RPAREN
92 27 RPAREN
93 39 BECOMES
93 39 COMMA
93 39 EQ
93 39 GE
93 39 GT
93 39 LE
93 39 LT
93 39 MINUS
93 39 NE
93 39 PCT
93 39 PLUS
93 39 RBRACK
93 39 RPAREN
93 39 SEMI
93 39 SLASH
93 39 STAR
95 10 ID
98 15 DELETE
98 15 ID
98 15 IF
98 15 LPAREN
98 15 PRINTLN
98 15 RBRACE
98 15 RETURN
98 15 STAR
98 15 WHILE
)END";

const std::string WLP4_COMBINED = WLP4_CFG+WLP4_TRANSITIONS+WLP4_REDUCTIONS+".END\n";



std::vector<std::vector<std::string>> after_act;
bool error = 0;

std::pair<bool, std::string> find_trans(
    std::string curr_state, std::string curr,
    std::vector<std::pair<std::pair<std::string, std::string>, std::string>> trans) {
  std::pair<bool, std::string> result;
  for (unsigned i = 0; i < trans.size(); i++) {
    std::string x = trans[i].first.first;
    std::string y = trans[i].first.second;
    std::string z = trans[i].second;
    if (x == curr_state && y == curr) {
        result = std::make_pair(true, z);
        return result;
    }
  }
  result = std::make_pair(false, "");
  return result;
}

std::pair<bool, std::string> find_reduce(std::string curr_state, std::string next, 
  std::vector<std::pair<std::pair<std::string, std::string>, std::string>> red) {
  std::pair<bool, std::string> result;
  for (unsigned i = 0; i < red.size(); i++) {
    std::string x = red[i].first.first;
    std::string y = red[i].first.second;
    std::string z = red[i].second;
    if (x == curr_state && z == next) {
        result = std::make_pair(true, y);
        return result;
    }
  }
  result = std::make_pair(false, "");
  return result;
}

void print(std::string act, unsigned int k, std::vector<std::string> reduction, 
           std::vector<std::string> input, std::vector<std::string> rules, int num,
           std::vector<std::string> lexme) {
            k = k - 2;
            std::vector<std::string> one;
    if (act == "shift") {
        //std::cout << input[k] << " " << lexme[k] << std::endl;
        one.emplace_back(input[k]);
        one.emplace_back(lexme[k]);
        after_act.emplace_back(one);
    } else {
        num = num * 2;
        if (rules[num + 1] == ".EMPTY") {
            //std::cout << rules[num] << std::endl;
            one.emplace_back(rules[num]);
            after_act.emplace_back(one);
        } else {
            //std::cout << rules[num] << " " << rules[num + 1] << std::endl;
            one.emplace_back(rules[num]);

            std::string a = "";
            std::string r = rules[num+1];
            for (unsigned int i = 0; i < r.size(); i++) {
              if (r[i] != ' ') {
                a.push_back(r[i]);
              } else {
                one.emplace_back(a);
                a = "";
              }
            }
            one.emplace_back(a);
            after_act.emplace_back(one);
        }
    }
}

std::pair<std::vector<std::string>, unsigned int> shift(
    unsigned int k, std::vector<std::string> reduction, 
    std::vector<std::string> input, std::vector<std::string> rules) {
    std::string curr = "";
    curr = input[k];
    reduction.emplace_back(curr);
    reduction.emplace_back(" ");
    k = k + 2;
    return std::make_pair(reduction, k);
}

std::pair<std::pair<std::vector<std::string>, std::string>, std::pair<int, std::string>> reduce (
  int r, unsigned int k, std::vector<std::string> reduction, 
  std::vector<std::string> input, std::vector<std::string> rules) {
    std::pair<std::pair<std::vector<std::string>, std::string>, std::pair<int, std::string>> result;
    int rule_number = r; 
    std::string lhs = rules[rule_number * 2];
    std::string rhs = rules[rule_number * 2 + 1];
    int num = 0;
    if (rhs == ".EMPTY") {
        reduction.emplace_back(lhs);
        reduction.emplace_back(" ");
    } else {
        reduction.pop_back();
        for (unsigned int i = 0; i < rhs.length(); i++) {
            if (rhs.substr(i,1) == " ") {
                num++;
            }
        }
        num = num * 2 + 1;
        for (int i = 0; i < num; i++) {
            reduction.pop_back();
        }
        if (lhs != ".EMPTY") {
            reduction.emplace_back(lhs);
            reduction.emplace_back(" ");
        }
    }
    result = std::make_pair(std::make_pair(reduction, lhs), std::make_pair(num, rhs));
    return result;
}

void action (std::vector<std::string> input, std::vector<std::string> rules,
std::vector<std::string> states, std::vector<std::string> reduction,
std::vector<std::pair<std::pair<std::string, std::string>, std::string>> red,
std::vector<std::pair<std::pair<std::string, std::string>, std::string>> trans,
std::vector<std::string> lexme) {
  unsigned int k = 0;                   //包括空格的总长度！！！！！！
  std::pair<std::vector<std::string>, unsigned int> shift_next;
  std::pair<std::pair<std::vector<std::string>, std::string>, std::pair<int, std::string>> red_next;
  std::pair<bool, std::string> trans_next;
  std::pair<bool, std::string> reduce_next;
  states.emplace_back("0");
  for (unsigned int i = 0; i < input.size(); i = i + 2) {
      // 先根据 curr_state 查reduce，有 -> reduce + 改state（state没有 -> error）
    //                            没有 -> 就判断能否shift
    reduce_next = find_reduce(states.back(), input[i], red);
    if (reduce_next.first == true) {
      std::stringstream ss;
      int rule_number = 0; 
      ss << reduce_next.second; 
      ss >> rule_number;
      red_next = reduce(rule_number, k, reduction, input, rules);
      reduction = red_next.first.first;
      print("reduce", k, reduction, input, rules, rule_number, lexme);

      if (red_next.second.second != ".EMPTY") {
        int state_pop = red_next.second.first / 2 + 1;
        for (int i = 0 ; i < state_pop; i++) {
        states.pop_back();
        }
      }
      trans_next = find_trans(states.back(), red_next.first.second, trans);
      if (trans_next.first == true) {
        states.emplace_back(trans_next.second);
      } else {
        k = k / 2;
        std::cerr << "ERROR at " << k << std::endl;
        error = 1;
        break;
      }
      i = i - 2;
    } else {
      trans_next = find_trans(states.back(), input[i], trans);
      //std::cout << states.back() << " " << input[i] << std::endl;
      if (trans_next.first == true) {
      states.emplace_back(trans_next.second);

      shift_next = shift(k, reduction, input, rules);
      reduction = shift_next.first;
      k = shift_next.second;
      print("shift", k, reduction, input, rules, 0, lexme);
      } else {
      k = k / 2;
      std::cout << states.back() << " " << input[i] << std::endl;
      std::cerr << "ERROR at " << k << std::endl;
      error = 1;
      break;
      }
    } 
  }
  //reduce最后一次
  reduce_next = find_reduce(states.back(), ".ACCEPT", red);
  if (reduce_next.first == true) {
    std::stringstream ss;
    int rule_number = 0; 
    ss << reduce_next.second; 
    ss >> rule_number;
    red_next = reduce(rule_number, k, reduction, input, rules);
    reduction = red_next.first.first;
    print("reduce", k, reduction, input, rules, rule_number, lexme);
  }
}

class Node {
  public:
  std::string LHS;
  std::vector<Node> RHS;
  unsigned int rhs_size;

  Node(std::string lhs, unsigned int size) {
    this->LHS = lhs;
    this->rhs_size = size;
    for (unsigned int i = 0; i < rhs_size; i++) {
      Node child {"", 0};
      this->RHS.emplace_back(child);
    }
  }
};


bool ter_find(std::vector<std::string> ter, std::string tag) {
  for (unsigned int i = 0; i < ter.size(); i++) {
    if (ter[i] == tag) {
      return true;
    }
  }
  return false;
}


Node tree(std::vector<std::string> ter) {
  std::vector<std::string> rule = after_act.back();
  after_act.pop_back();

  unsigned int rhs_size = rule.size() - 1;
  std::string LHS = rule[0];
  Node root {LHS, rhs_size};
  if (ter_find(ter, LHS)) {
    root.RHS[0] = Node(rule[1], 0);
    return root;
  }
  //recursion:
  for (int i = rhs_size - 1; i >= 0; i--) {
    root.RHS[i] = tree(ter);
  }
  return root;
}


void printtree(Node& root, std::vector<std::string> ter) {
  if (ter_find(ter, root.LHS)) {
    std::cout << root.LHS << " " << root.RHS[0].LHS << std::endl;
    return;
  }
  
  std::cout << root.LHS;
  if (root.rhs_size == 0) {
    std::cout << " " << ".EMPTY";
  } else {
    for (unsigned int i = 0; i < root.rhs_size; i++) {
      std::cout << " " << root.RHS[i].LHS;
    }
  }
  std::cout << std::endl;

  for (unsigned int i = 0; i < root.rhs_size; i++) {
    printtree(root.RHS[i], ter);
  }
}








int main() {
  std::string s;
  std::vector<std::string> rules;
  std::vector<std::string> states;
  std::vector<std::string> reduction;
  std::stringstream ss;
  ss << WLP4_COMBINED;

  // read rules
  std::getline(ss, s);
  while (ss >> s) {
    if (s == ".TRANSITIONS") {
        break;
    }
    rules.emplace_back(s);
    std::string line;
    std::getline(ss, line);
    line = line.substr(1);
    rules.emplace_back(line);
  }
  // read transitions
  std::getline(ss, s);
  std::vector<std::pair<std::pair<std::string, std::string>, std::string>> trans;
  std::string x, y ,z;
  while(ss >> s) {
    if (s == ".REDUCTIONS") {
        break;
    }
    x = s;
    ss >> y;
    ss >> z;
    trans.emplace_back(make_pair(make_pair(x, y), z));
  }

  // read reduction
  std::getline(ss, s);
  std::vector<std::pair<std::pair<std::string, std::string>, std::string>> red;
  while(ss >> s) {
    if (s == ".END") {
        break;
    }
    x = s;
    ss >> y;
    ss >> z;
    red.emplace_back(make_pair(make_pair(x, y), z));
  }

  //read input
  std::istream& in = std::cin;
  std::vector<std::string> input;
  std::vector<std::string> lexme;
  input.emplace_back("BOF");
  input.emplace_back(" ");
  lexme.emplace_back("BOF");
  lexme.emplace_back(" ");
  while (in >> s) {
    input.emplace_back(s);
    input.emplace_back(" ");
    in >> s;
    lexme.emplace_back(s);
    lexme.emplace_back(" ");
  }
  input.emplace_back("EOF");
  lexme.emplace_back("EOF");

  action(input, rules, states, reduction, red, trans, lexme);

  // for (unsigned int i = 0; i < after_act.size(); i++) {
  //   for (unsigned int j = 0; j < after_act[i].size(); j++) {
  //     std::cout << after_act[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  if (error == 0) {
    Node root  = tree(input);
    printtree(root, input);
  }
}
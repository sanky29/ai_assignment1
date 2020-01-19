date
./compile.sh
./run1.sh T_S_1
minisat T_S_1.satinput T_S_1.satoutput
./run2.sh T_S_1
python format_checker_new.py T_S_1.graphs T_S_1.mapping
date
./run1.sh T_S_2
minisat T_S_2.satinput T_S_2.satoutput
./run2.sh T_S_2
python format_checker_new.py T_S_2.graphs T_S_2.mapping
date
./run1.sh Unsat
minisat Unsat.satinput Unsat.satoutput
./run2.sh Unsat
python format_checker_new.py Unsat.graphs Unsat.mapping
date
./run1.sh T_M_2
minisat T_M_2.satinput T_M_2.satoutput
./run2.sh T_M_2
python format_checker_new.py T_M_2.graphs T_M_2.mapping
date
./run1.sh T_M_4
minisat T_M_4.satinput T_M_4.satoutput
./run2.sh T_M_4
python format_checker_new.py T_M_4.graphs T_M_4.mapping
date
./run1.sh T_L_1
minisat T_L_1.satinput T_L_1.satoutput
./run2.sh T_L_1
python format_checker_new.py T_L_1.graphs T_L_1.mapping
date

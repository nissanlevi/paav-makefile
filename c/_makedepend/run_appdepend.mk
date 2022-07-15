bin/run_g: obj_412/run_app..version_g.o obj_412/pa_parser.y_g.o obj_412/pa_parser.l_g.o obj_412/assertion_g.o obj_412/assigned_val_g.o obj_412/command_g.o obj_412/expr_g.o obj_412/line_command_g.o obj_412/logger_g.o obj_412/main_g.o obj_412/program_g.o obj_412/traverse_g.o obj_412/yacc_functions_g.o  c/_makedepend/applink
	$(MAKEAPPDIR)
	$(PARALLEL_WRAP) $(LINKWRAP) $(LINK.cc)  -o $@ obj_412/run_app..version_g.o obj_412/pa_parser.y_g.o obj_412/pa_parser.l_g.o obj_412/assertion_g.o obj_412/assigned_val_g.o obj_412/command_g.o obj_412/expr_g.o obj_412/line_command_g.o obj_412/logger_g.o obj_412/main_g.o obj_412/program_g.o obj_412/traverse_g.o obj_412/yacc_functions_g.o -lnsl  
	@echo Done building $(TYPE) $@.
	@echo

bin/run: obj_412/run_app..version.o obj_412/pa_parser.y.o obj_412/pa_parser.l.o obj_412/assertion.o obj_412/assigned_val.o obj_412/command.o obj_412/expr.o obj_412/line_command.o obj_412/logger.o obj_412/main.o obj_412/program.o obj_412/traverse.o obj_412/yacc_functions.o    c/_makedepend/applink
	$(MAKEAPPDIR)
	$(PARALLEL_WRAP) $(LINKWRAP) $(filter-out -I%,$(LINK.cc))  -o $@ obj_412/run_app..version.o obj_412/pa_parser.y.o obj_412/pa_parser.l.o obj_412/assertion.o obj_412/assigned_val.o obj_412/command.o obj_412/expr.o obj_412/line_command.o obj_412/logger.o obj_412/main.o obj_412/program.o obj_412/traverse.o obj_412/yacc_functions.o   -lnsl    
	@echo Done building $(TYPE) $@.
	@echo

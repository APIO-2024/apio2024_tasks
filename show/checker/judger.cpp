#include "uoj_judger.h"

struct MySubtaskInfo {
	bool passed;
	double score;

	MySubtaskInfo() {
	}
	MySubtaskInfo(const bool &_p, const double &_s)
		: passed(_p), score(_s){}
};
inline std::vector<std::string> split_zr(const std::string & str) {
	std::vector<std::string> ret;
	std::string T;
	for(char c : str) {
		if(c == '\0') {
			ret.emplace_back(T), T = "";
		} else {
			T += c;
		}
	}
	return ret;
}
inline std::string to_string(const std::vector<std::string> & A) {
	std::string result = A[0];
	for(int i = 1;i < (int) A.size();++i) {
		result += " ";
		result += A[i];
	}
	return result;
}
inline std::string conf_str_must(std::string a, int id) {
	static const std::string name = "aushdfasdjfk fuck you matasdfkuas";
	std::string res = conf_str(a + "_" + std::to_string(id), name);
	if(res == name) {
		exit(1);
	}
	return res;
}
void Add_point_info(const PointInfo &info, bool update_tot_score = true) {
	const int ust = info.ust;
	const int usm = info.usm;
	const int a0 = ust >= 0 ? ust >> 16 : -1;
	const int a1 = ust >= 0 ? ust % 65536 : -1;
	const int b0 = usm >= 0 ? usm >> 16 : -1;
	const int b1 = usm >= 0 ? usm % 65536 : -1;
	if (info.num >= 0) {
		if(info.ust >= 0) {
			tot_time += a0 + a1;
			max_time = max(max_time, a0 + a1);
		}
		if(info.usm >= 0) {
			max_memory = max(max_memory, b0);
			max_memory = max(max_memory, b1);
		}
	}
	if (update_tot_score) {
		tot_score += info.scr;
	}


	details_out << "<test num=\"" << info.num << "\""
		<< " score=\"" << info.scr << "\""
		<< " info=\"" << htmlspecialchars(info.info) << "\""
		<< " time=\"" << a0+a1 << "ms = " << a0 << "ms + " << a1 << "\""
		<< " memory=\"" << b0 << "kb," << b1 << "\">" << endl;
	std::vector<std::string> in = split_zr(info.in);
	std::vector<std::string> out = split_zr(info.out);
	for(int i = 0; i < (int) in.size();++i) {
		if (conf_str("show_in", "off") == "on") {
			details_out << "<in>" << htmlspecialchars(in[i]) << "</in>" << endl;
		}
		if (conf_str("show_out", "off") == "on") {
			details_out << "<out>" << htmlspecialchars(out[i]) << "</out>" << endl;
		}
	}
	if (conf_str("show_res", "on") == "off") {
		details_out << "<res>" << htmlspecialchars(info.res) << "</res>" << endl;
	}
	details_out << "</test>" << endl;
}
void Add_subtask_info(const int &num, const double &scr, const string &info, const vector<PointInfo> &points) {
	details_out << "<subtask num=\"" << num << "\""
		<< " score=\"" << scr << "\""
		<< " info=\"" << htmlspecialchars(info) << "\">" << endl;
	tot_score += scr;
	for (vector<PointInfo>::const_iterator it = points.begin(); it != points.end(); it++) {
		Add_point_info(*it, false);
	}
	details_out << "</subtask>" << endl;
}


inline std::vector<std::string> split(const std::string & str) {
	std::vector<std::string> ret;
	std::string T;
	for(char c : str) {
		if(c == ',') {
			if(T != "") ret.emplace_back(T), T = "";
		} else {
			T += c;
		}
	}
	if(T != "") ret.emplace_back(T);
	return ret;
}
inline RunCompilerResult precompile() {
	return compile_with_implementer("answer");
}
struct cmds {
	RunLimit limit;
	std::string input;
	std::string output;
	std::string error;
	std::string result;
	std::string name;
	std::vector<std::string> readable;
	std::vector<std::string> writable;
	std::vector<std::string> ops;
};
inline RunResult run(const cmds & s) {
	std::vector<std::string> OP;
	for(const auto & x : s.readable) OP.push_back("--add-readable=" + x);
	for(const auto & x : s.writable) OP.push_back("--add-writable=" + x);
	OP.push_back(s.name);
	for(const auto & x : s.ops) OP.push_back(x);
	return vrun_program(s.result.c_str(), s.input.c_str(), s.output.c_str(), s.error.c_str(), s.limit, OP);
}
inline PointInfo super_test_point(int id, TestPointConfig tpc = TestPointConfig()) {
	tpc.auto_complete(id);
	int cc = conf_int("n_judgecmd", 0);
	const auto getfile = [&](const std::string & str) {
		if(str == "checker") {
			return conf_str(str);
		}
		if(str == "none") {
			return std::string("/dev/null");
		}
		if(str == "INPUT") {
			return tpc.input_file_name;
		}
		if(str == "OUTPUT") {
			return tpc.output_file_name;
		}
		if(str == "ANSWER") {
			return tpc.answer_file_name;
		}
		return work_path + "/" + str;
	};

	if(conf_is("validate_input_before_test", "on")) {
		RunValidatorResult val_ret = run_validator(
				getfile("INPUT").c_str(),
				conf_run_limit("validator", 0, RL_VALIDATOR_DEFAULT),
				conf_str("validator"));
		if (val_ret.type != runp::RS_AC) {
			return PointInfo(id, 0, -1, -1,
					"Validator " + info_str(val_ret.type),
					file_preview(getfile("INPUT")), "",
					"");
		} else if (!val_ret.succeeded) {
			return PointInfo(id, 0, -1, -1,
					"Invalid Input",
					file_preview(getfile("INPUT")), "",
					val_ret.info);
		}
	}
	std::string in, out;

	int T = -1, M = -1;
	for(int part = 1;part <= cc;++part) {
		cmds cmd;
		std::string name = conf_str_must("run_prog", part);
		std::string input = conf_str_must("run_prog_input", part);
		std::string output = conf_str_must("run_prog_output", part);
		std::string error = result_path + "/" + name + "_error.txt";
		std::string result = result_path + "/" + name + "_result.txt";

		if(conf_str("in_datapath", part, "") == "yes") {
			name = data_path + "/" + name;
		} else {
			name = getfile(name);
		}
		input = getfile(input);
		output = getfile(output);

		int TL = conf_int("run_time_limit", part, 1) * 1000;
		int ML = conf_int("run_memory_limit", part, 512);
		int OL = conf_int("run_output_limit", part, 64);

		cmd.limit = RunLimit(TL, ML, OL);
		cmd.input = input;
		cmd.output = output;
		cmd.error = error;
		cmd.result = result;
		cmd.name = name;

		std::string READABLE = conf_str("readablefiles", part, "");
		cmd.readable = split(READABLE);
		for(auto & str : cmd.readable) {
			str = getfile(str);
		}

		std::string WRITABLE = conf_str("writablefiles", part, "");
		cmd.writable = split(WRITABLE);
		for(auto & str : cmd.writable) {
			str = getfile(str);
		}

		std::string PARAM = conf_str("params", part, "");
		cmd.ops = split(PARAM);
		for(auto & str : cmd.ops) {
			str = getfile(str);
		}


		RunResult qwq = run(cmd);
		if(part == 1) {
			T &= (int)qwq.ust << 16 | -1u >> 16;
			M &= (int)qwq.usm << 16 | -1u >> 16;
		}
		if(part == 3) {
			T &= (int)qwq.ust | -1u << 16;
			M &= (int)qwq.usm | -1u << 16;
		}

		if(conf_str("show", part, "") == "yes") {
			auto A = conf_str("show_input", part, "");
			if(A.size()) A = getfile(A);
			else A = input;
			auto B = conf_str("show_output", part, "");
			if(B.size()) B = getfile(B);
			else B = output;
			in += file_preview(A) + '\0';
			out += file_preview(B) + '\0';
		}

		if(qwq.type != runp::RS_AC) {
			return PointInfo(id, 0, -1, -1,
				info_str(qwq.type),
				in,
				out,
				""
			);
		}
		if(cc == part) {
			RunCheckerResult chk_ret = RunCheckerResult::from_file( error, qwq);
			return PointInfo(id, chk_ret.scr, T, M,
				"default",
				in,
				out,
				chk_ret.info
			);
		}
	}
}
void ordinary_test() {
	int n = conf_int("n_tests", 10);
	int m = conf_int("n_ex_tests", 0);
	int nT = conf_int("n_subtasks", 0);

	report_judge_status_f("Compiling");
	RunCompilerResult c_ret = precompile();
	if (!c_ret.succeeded) {
		end_judge_compile_error(c_ret);
	}


	bool passed = true;
	if (nT == 0) {
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Test #%d", i);
			PointInfo po = super_test_point(i);
			if (po.scr != 100) {
				passed = false;
			}
			po.scr = scale_score(po.scr, conf_double("point_score", i, 100 / n));
			Add_point_info(po);
		}
	} else if (nT == 1) {
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Test #%d", i);
			PointInfo po = super_test_point(i);
			if (po.scr != 100) {
				passed = false;
				po.scr = i == 1 ? 0 : -100;
				Add_point_info(po);
				break;
			} else {
				po.scr = i == 1 ? 100 : 0;
				Add_point_info(po);
			}
		}
	} else {
		map<int, MySubtaskInfo> subtasks;
		map<int,double> minScore;
		for (int t = 1; t <= nT; t++) {
			string subtaskType = conf_str("subtask_type", t, "packed");
			int startI = conf_int("subtask_end", t - 1, 0) + 1;
			int endI = conf_int("subtask_end", t, 0);

			vector<PointInfo> points;
			minScore[t] = 100;

			vector<int> dependences;
			if (conf_str("subtask_dependence", t, "none") == "many") {
				string cur = "subtask_dependence_" + vtos(t);
				int p = 1;
				while (conf_int(cur, p, 0) != 0) {
					dependences.push_back(conf_int(cur, p, 0));
					p++;
				}
			} else if (conf_int("subtask_dependence", t, 0) != 0) {
				dependences.push_back(conf_int("subtask_dependence", t, 0));
			}
			bool skipped = false;
			for (vector<int>::iterator it = dependences.begin(); it != dependences.end(); it++) {
				if (subtaskType == "packed") {
					if (!subtasks[*it].passed) {
						skipped = true;
						break;
					}
				} else if (subtaskType == "min") {
					minScore[t] = min(minScore[t], minScore[*it]);
				}
			}
			if (skipped) {
				Add_subtask_info(t, 0, "Skipped", points);
				continue;
			}

			double tfull = conf_double("subtask_score", t, 100.0 / nT);
			double tscore = scale_score(minScore[t], tfull);
			string info = "Accepted";
			for (int i = startI; i <= endI; i++) {
				report_judge_status_f("Judging Test #%d of Subtask #%d", i, t);
				PointInfo po = super_test_point(i);
				if (subtaskType == "packed") {
					if (po.scr != 100) {
						passed = false;
						po.scr = i == startI ? 0 : -tfull;
						tscore = 0;
						points.push_back(po);
						info = po.info;
						break;
					} else {
						po.scr = i == startI ? tfull : 0;
						tscore = tfull;
						points.push_back(po);
					}
				} else if (subtaskType == "min") {
					minScore[t] = min(minScore[t], po.scr);
					if (po.scr != 100) {
						passed = false;
					}
					po.scr = scale_score(po.scr, tfull);
					if (po.scr <= tscore) {
						tscore = po.scr;
						points.push_back(po);
						info = po.info;
					} else {
						points.push_back(po);
					}
					if(po.scr == 0) {
						break;
					}
				}
			}

			subtasks[t] = MySubtaskInfo(info == "Accepted", tscore);

			Add_subtask_info(t, tscore, info, points);
		}
	}
	if (!passed) {
		end_judge_ok();
	}

	tot_score = 100;
	for (int i = 1; i <= m; i++) {
		report_judge_status_f("Judging Extra Test #%d", i);
		PointInfo po = super_test_point(-i);
		if (po.scr != 100) {
			po.num = -1;
			po.info = "Extra Test Failed : " + po.info + " on " + vtos(i);
			po.scr = -3;
			Add_point_info(po);
			end_judge_ok();
		}
	}
	if (m != 0) {
		PointInfo po(-1, 0, -1, -1, "Extra Test Passed", "", "", "");
		Add_point_info(po);
	}
	end_judge_ok();
}

PointInfo super_test_hack_point(const string &name, TestPointConfig tpc) {
	tpc.submit_answer = false;
	tpc.validate_input_before_test = false;
	tpc.auto_complete(0);
	RunValidatorResult val_ret = run_validator(
			tpc.input_file_name,
			conf_run_limit("validator", 0, RL_VALIDATOR_DEFAULT),
			conf_str("validator"));
	if (val_ret.type != runp::RS_AC) {
		return PointInfo(0, 0, -1, -1,
				"Validator " + info_str(val_ret.type),
				file_preview(tpc.input_file_name), "",
				"");
	} else if (!val_ret.succeeded) {
		return PointInfo(0, 0, -1, -1,
				"Invalid Input",
				file_preview(tpc.input_file_name), "",
				val_ret.info);
	}

	execute(("touch " + tpc.answer_file_name).c_str());

	PointInfo po = super_test_point(0, tpc);
	po.scr = po.scr != 100;
	return po;
}

void hack_test() {
	RunCompilerResult c_ret = precompile();
	if (!c_ret.succeeded) {
		end_judge_compile_error(c_ret);
	}
	TestPointConfig tpc;
	tpc.input_file_name = work_path + "/hack_input.txt";
	tpc.output_file_name = work_path + "/pro_output.txt";
	tpc.answer_file_name = work_path + "/std_output.txt";

	PointInfo po = super_test_hack_point("answer", tpc);
	if(po.info == "Invalid Input")
		add_point_info(po);
	else
		Add_point_info(po);
	end_judge_ok();
}

void sample_test() {
	report_judge_status_f("Compiling");
	RunCompilerResult c_ret = precompile();
	if (!c_ret.succeeded) {
		end_judge_compile_error(c_ret);
	}

	int n = conf_int("n_sample_tests", 0);
	bool passed = true;
	for (int i = 1; i <= n; i++) {
		report_judge_status_f("Judging Sample Test #%d", i);
		PointInfo po = super_test_point(-i);
		po.num = i;
		if (po.scr != 100) {
			passed = false;
		}
		po.scr = scale_score(po.scr, 100 / n);
		Add_point_info(po);
	}
	if (passed) {
		tot_score = 100;
	}
	end_judge_ok();
}

void custom_test() {
	report_judge_status_f("Compiling");
	RunCompilerResult c_ret = precompile();
	if (!c_ret.succeeded) {
		end_judge_compile_error(c_ret);
	}

	report_judge_status_f("Judging");
	add_custom_test_info(ordinary_custom_test("answer"));

	end_judge_ok();
}

int main(int argc, char **argv) {
	judger_init(argc, argv);

	if (conf_is("test_new_hack_only", "on")) {
		hack_test();
	} else if (conf_is("test_sample_only", "on")) {
		sample_test();
	} else if (conf_is("custom_test", "on")) {
		custom_test();
	} else {
		ordinary_test();
	}
}

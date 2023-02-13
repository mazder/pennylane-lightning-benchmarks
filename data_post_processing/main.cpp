#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
using std::setw;

// gcc vs clang in bare-metal
// gcc vs clang in container
// gcc bare-metal vs gcc container
// clang bare-metal vs clang container

void gate_to_gate_float_double(vector<string>& gate_name, vector< vector<long int> >& time_cpu_it){

    // devide float and double
    int k=0;

    vector<string> f_gate_name;
    vector< vector<long int> > f_time_cpu_it;

    vector<string> d_gate_name;
    vector< vector<long int> > d_time_cpu_it;

    for(int i=0; i<gate_name.size(); i++){
        if (gate_name[i].find("<float>") != std::string::npos) {
                 f_gate_name.push_back(gate_name[i]);
                 f_time_cpu_it.push_back(time_cpu_it[i]);
        }

        if (gate_name[i].find("<double>") != std::string::npos) {
                 d_gate_name.push_back(gate_name[i]);
                 d_time_cpu_it.push_back(time_cpu_it[i]);
        }
    }

    // print
    cout<<"Float size == Double size "<<f_gate_name.size()<<" "<<d_gate_name.size()<<endl;
    cout<<" FLOAT====================================================="<<endl;

    vector< long int> total_float, total_double;

    long int t=0,c=0,it=0;
    for(int i=0; i<f_gate_name.size(); i++){
        cout <<f_gate_name[i]<<" "<<f_time_cpu_it[i][0]<<" "<<f_time_cpu_it[i][1]<<" "<<f_time_cpu_it[i][2]<<endl;
        t=t+ f_time_cpu_it[i][0];
        c=c+f_time_cpu_it[i][1];
        it=it+f_time_cpu_it[i][2];
    }
    total_float.push_back(t);
    total_float.push_back(c);
    total_float.push_back(it);


    cout<<" DOUBLE====================================================="<<endl;
    t=0,c=0,it=0;
    for(int i=0; i<d_gate_name.size(); i++){
        cout <<d_gate_name[i]<<" "<<d_time_cpu_it[i][0]<<" "<<d_time_cpu_it[i][1]<<" "<<d_time_cpu_it[i][2]<<endl;
        t=t+ d_time_cpu_it[i][0];
        c=c+d_time_cpu_it[i][1];
        it=it+d_time_cpu_it[i][2];
    }

    total_double.push_back(t);
    total_double.push_back(c);
    total_double.push_back(it);

    cout <<"\n\n========Total Float Vs Total Double========"<<endl;
    cout<<"F & "<<total_float[0]<<" & "<<total_float[1]<<" & "<<total_float[2]<<" \\\\ \\ hline"<<endl;
    cout<<"D & "<<total_double[0]<<" & "<<total_double[1]<<" & "<<total_double[2]<<" \\\\ \\ hline"<<endl;
    cout<<"F+D & "<<total_double[0]+total_float[0] \
                                   <<" & "<<total_double[1]+total_float[1] \
                                   <<" & "<<total_double[2]+total_float[2]<<" \\\\ \\ hline"<<endl;
    cout<<"100*(D-F)/D & "<<(double)100*(total_double[0]-total_float[0])/total_double[0] \
                                   <<" & "<<(double)100*(total_double[1]-total_float[1])/total_double[1] \
                                   <<" & "<<(double)100*(total_double[2]-total_float[2])/total_double[2]<<" \\\\ \\ hline"<<endl;

}

void read_data(char *arg1, char *arg2){
    std::ifstream gcc_infile(arg1);
    std::ifstream clang_infile(arg2);

    vector<string> gcc_gate;
    vector<string> clang_gate;

    vector< vector<long int> > gcc_time_cpu_it;
    vector< vector<long int> > clang_time_cpu_it;

    int i=0,total_nop=0;
    long int total_gcc_real_time=0, total_gcc_cpu_time=0, total_gcc_it=0;
    long int total_clang_real_time=0, total_clang_cpu_time=0, total_clang_it=0;

    std::string gcc_line,clang_line;
    int gindex=0;
    while (std::getline(gcc_infile, gcc_line) && std::getline(clang_infile, clang_line)){
        i++;
        if(i==11){
        std::cout<<gcc_line<<"    vs      "<<clang_line<<std::endl;
        }
        if((i>=23) && (gcc_line.compare("\n")!=0) && (clang_line.compare("\n")!=0) ){
            total_nop++;
            std::istringstream gcc_iss(gcc_line);
            std::istringstream clang_iss(clang_line);

            string gcc_name, gcc_ns1, gcc_ns2;
            long int gcc_real_time, gcc_cpu_time, gcc_it;
            string clang_name, clang_ns1, clang_ns2;
            long int clang_real_time, clang_cpu_time, clang_it;

            if(!(gcc_iss >> gcc_name >> gcc_real_time >> gcc_ns1 >> gcc_cpu_time >> gcc_ns2 >> gcc_it)){break;}
            if(!(clang_iss >> clang_name >> clang_real_time >> clang_ns1 >> clang_cpu_time >> clang_ns2 >> clang_it)){break;}

            total_gcc_real_time = total_gcc_real_time + gcc_real_time;
            total_gcc_cpu_time = total_gcc_cpu_time + gcc_cpu_time;
            total_gcc_it = total_gcc_it + gcc_it;

            total_clang_real_time = total_clang_real_time + clang_real_time;
            total_clang_cpu_time = total_clang_cpu_time + clang_cpu_time;
            total_clang_it = total_clang_it + clang_it;

            gindex++;
            if(gindex==10){

                gcc_gate.push_back(gcc_name);
                vector<long int>gcc_t_c_i;
                gcc_t_c_i.push_back(total_gcc_real_time);
                gcc_t_c_i.push_back(total_gcc_cpu_time);
                gcc_t_c_i.push_back(total_gcc_it);
                gcc_time_cpu_it.push_back(gcc_t_c_i);

                clang_gate.push_back(clang_name);
                vector<long int>clang_t_c_i;
                clang_t_c_i.push_back(total_clang_real_time);
                clang_t_c_i.push_back(total_clang_cpu_time);
                clang_t_c_i.push_back(total_clang_it);
                clang_time_cpu_it.push_back(clang_t_c_i);

                total_gcc_real_time = 0;
                total_gcc_cpu_time = 0;
                total_gcc_it = 0;

                total_clang_real_time = 0;
                total_clang_cpu_time = 0;
                total_clang_it = 0;
                gindex=0;
            }
        }
    }
    cout<<"Total number of Operations: "<<total_nop<<endl;
    cout<<"Total number of Gates: "<<gcc_gate.size()<<"=="<<clang_gate.size()<<endl;

    cout<<"===================gcc analysis===================="<<endl;
    gate_to_gate_float_double(gcc_gate, gcc_time_cpu_it);

    cout<<"===================clang analysis===================="<<endl;
    gate_to_gate_float_double(clang_gate, clang_time_cpu_it);

}



void gate_gate_gcc_clang(char *arg1, char *arg2){
    std::ifstream gcc_infile(arg1);
    std::ifstream clang_infile(arg2);

    vector<string> gcc_gate;
    vector<string> clang_gate;

    vector<long int> gcc_total_real;
    vector<long int> gcc_total_cpu;
    vector<long int> gcc_total_it;

    vector<long int> clang_total_real;
    vector<long int> clang_total_cpu;
    vector<long int> clang_total_it;




    int i=0,total_nop=0;
    // To capture how many operations (out of total_nop) speed up when using clang
    int nop_clang_dominant_real_time=0;
    int nop_clang_dominant_cpu_time=0;
    int nop_clang_dominant_it=0;

    long int total_gcc_real_time=0, total_gcc_cpu_time=0, total_gcc_it=0;
    long int total_clang_real_time=0, total_clang_cpu_time=0, total_clang_it=0;



    std::string gcc_line,clang_line;
    int gindex=0;
    while (std::getline(gcc_infile, gcc_line) && std::getline(clang_infile, clang_line)){
        i++;
        if(i==11){
        std::cout<<gcc_line<<"    vs      "<<clang_line<<std::endl;
        }
        if((i>=23) && (gcc_line.compare("\n")!=0) && (clang_line.compare("\n")!=0) ){

            std::istringstream gcc_iss(gcc_line);
            std::istringstream clang_iss(clang_line);

            string gcc_name, gcc_ns1, gcc_ns2;
            long int gcc_real_time, gcc_cpu_time, gcc_it;
            string clang_name, clang_ns1, clang_ns2;
            long int clang_real_time, clang_cpu_time, clang_it;

            if(!(gcc_iss >> gcc_name >> gcc_real_time >> gcc_ns1 >> gcc_cpu_time >> gcc_ns2 >> gcc_it)){break;}
            if(!(clang_iss >> clang_name >> clang_real_time >> clang_ns1 >> clang_cpu_time >> clang_ns2 >> clang_it)){break;}

            total_gcc_real_time = total_gcc_real_time + gcc_real_time;
            total_gcc_cpu_time = total_gcc_cpu_time + gcc_cpu_time;
            total_gcc_it = total_gcc_it + gcc_it;

            total_clang_real_time = total_clang_real_time + clang_real_time;
            total_clang_cpu_time = total_clang_cpu_time + clang_cpu_time;
            total_clang_it = total_clang_it + clang_it;

            gindex++;
            if(gindex==10){
                //std::cout<<"gcc "<<gcc_name<<" "<<total_gcc_real_time<<" "<<total_gcc_cpu_time <<" "<<total_gcc_it<<std::endl;
                //std::cout<<"clang "<<clang_name<<" "<<total_clang_real_time<<" "<<total_clang_cpu_time <<" "<<total_clang_it<<std::endl;

                //std::cout<<"compare "<<(double)100*(total_gcc_real_time-total_clang_real_time)/total_gcc_real_time <<" "\
                         <<(double)100*(total_gcc_cpu_time-total_clang_cpu_time)/total_gcc_cpu_time << " "\
                         <<(double)100*(total_gcc_it-total_clang_it)/total_gcc_it<<"\n"<<std::endl;

                gcc_gate.push_back(gcc_name);
                gcc_total_real.push_back(total_gcc_real_time);
                gcc_total_cpu.push_back(total_gcc_cpu_time);
                gcc_total_it.push_back(total_gcc_it);

                clang_gate.push_back(clang_name);
                clang_total_real.push_back(total_clang_real_time);
                clang_total_cpu.push_back(total_clang_cpu_time);
                clang_total_it.push_back(total_clang_it);

                total_gcc_real_time = 0;
                total_gcc_cpu_time = 0;
                total_gcc_it = 0;

                total_clang_real_time = 0;
                total_clang_cpu_time = 0;
                total_clang_it = 0;
                gindex=0;

            }

        }
    }

    std::cout<<gcc_gate.size()<<"=="<<clang_gate.size()<<std::endl;
    int clang_dominat=0;

    cout<<"GCC Vs Clang"<<endl;


    vector< vector<double> > float_data;
    vector< vector<double> > double_data;
    vector<string> gate_name_float;
    vector<string> gate_name_double;

    for(int i=0; i<gcc_gate.size(); i++){
        for(int j=0;j<clang_gate.size(); j++){
            if(gcc_gate[i]==clang_gate[j]){
                //cout<<"gcc   "<<gcc_gate[i]<<" "<<gcc_total_real[i]<<" "<<gcc_total_cpu[i]<<" "<<gcc_total_it[i]<<endl;
                //cout<<"clang "<<clang_gate[j]<<" "<<clang_total_real[j]<<" "<<clang_total_cpu[j]<<" "<<clang_total_it[j]<<endl;

                cout<<gcc_gate[i]<<" "<<(double)100*(gcc_total_real[i]-clang_total_real[j])/gcc_total_real[i]<<" "\
                <<(double)100*(gcc_total_cpu[i]-clang_total_cpu[j])/gcc_total_cpu[i]<<" "\
                <<(double)100*(gcc_total_it[i]-clang_total_it[j])/gcc_total_it[i]<<endl;


                double r = (double)100*(gcc_total_real[i]-clang_total_real[j])/gcc_total_real[i];
                double c = (double)100*(gcc_total_cpu[i]-clang_total_cpu[j])/gcc_total_cpu[i];
                double it = (double)100*(gcc_total_it[i]-clang_total_it[j])/gcc_total_it[i];



                vector<double> d;
                vector<double> f;

                if (gcc_gate[i].find("float") != std::string::npos) {
                        //std::cout << "float found!" << '\n';
                        gate_name_float.push_back(gcc_gate[i]);
                        f.push_back(r);
                        f.push_back(c);
                        f.push_back(it);
                        float_data.push_back(f);
                }

                if (gcc_gate[i].find("double") != std::string::npos) {
                        //std::cout << "double found!" << '\n';
                        gate_name_double.push_back(gcc_gate[i]);
                        d.push_back(r);
                        d.push_back(c);
                        d.push_back(it);
                        double_data.push_back(d);
                }

                if(gcc_total_cpu[i]-clang_total_cpu[j]>0){
                    clang_dominat++;
                }

            }
        }
    }


    std::cout<<double_data.size()<<"=="<<float_data.size()<<std::endl;
    cout<<"====================================================================================="<<endl;
    for(int i=0; i<double_data.size(); i++){

        cout<<gate_name_float[i]<<" "<<float_data[i][0]<<" "<<float_data[i][1]<<" "<<float_data[i][2]<<" "\
            <<gate_name_double[i]<<" "<<double_data[i][0]<<" "<<double_data[i][1]<<" "<<double_data[i][2]<<endl;

    }
    cout<<"====================================================================================="<<endl;
    for(int i=0; i<double_data.size(); i++){

        if ((gcc_gate[i].substr(0,5)=="CNOT<") || \
            (gcc_gate[i].substr(0,12)=="GeneratorRX<") || \
            (gcc_gate[i].substr(0,12)=="GeneratorRY<") || \
            (gcc_gate[i].substr(0,12)=="GeneratorRZ<")  || \
            (gcc_gate[i].substr(0,9)=="Hadamard<")  || \
            (gcc_gate[i].substr(0,8)=="IsingXX<")  || \
            (gcc_gate[i].substr(0,8)=="IsingXY<")  || \
            (gcc_gate[i].substr(0,8)=="IsingYY<")  || \
            (gcc_gate[i].substr(0,8)=="IsingZZ<")  || \
            (gcc_gate[i].substr(0,7)=="PauliX<")  || \
            (gcc_gate[i].substr(0,7)=="PauliY<")  || \
            (gcc_gate[i].substr(0,7)=="PauliZ<")  || \
            (gcc_gate[i].substr(0,11)=="PhaseShift<")  || \
            (gcc_gate[i].substr(0,4)=="Rot<")  || \
            (gcc_gate[i].substr(0,3)=="RX<")  || \
            (gcc_gate[i].substr(0,3)=="RY<")  || \
            (gcc_gate[i].substr(0,3)=="RZ<")  || \
            (gcc_gate[i].substr(0,2)=="S<")  || \
            (gcc_gate[i].substr(0,14)=="SingleQubitOp<")  || \
            (gcc_gate[i].substr(0,5)=="SWAP<")  || \
            (gcc_gate[i].substr(0,2)=="T<") ){
                cout<<gate_name_float[i]<<" "<<float_data[i][0]<<" "<<float_data[i][1]<<" "<<float_data[i][2]<<" "\
                <<gate_name_double[i]<<" "<<double_data[i][0]<<" "<<double_data[i][1]<<" "<<double_data[i][2]<<endl;
            }
    }
















    cout<<"GCC dominant: "<<gcc_gate.size()-clang_dominat<<" CLANG dominat: "<< clang_dominat<<endl;

}



void one_vs_other(char *arg1, char *arg2){


    std::ifstream gcc_infile(arg1);
    std::ifstream clang_infile(arg2);

    int i=0,total_nop=0;
    // To capture how many operations (out of total_nop) speed up when using clang
    int nop_clang_dominant_real_time=0;
    int nop_clang_dominant_cpu_time=0;
    int nop_clang_dominant_it=0;

    long int total_gcc_real_time=0, total_gcc_cpu_time=0, total_gcc_it=0;
    long int total_clang_real_time=0, total_clang_cpu_time=0, total_clang_it=0;

    std::string gcc_line,clang_line;

    while (std::getline(gcc_infile, gcc_line) && std::getline(clang_infile, clang_line)){
        i++;
        if(i==11){
        std::cout<<gcc_line<<"    vs      "<<clang_line<<std::endl;
        }
        if((i>=23) && (gcc_line.compare("\n")!=0) && (clang_line.compare("\n")!=0) ){
            total_nop++;

            std::istringstream gcc_iss(gcc_line);
            std::istringstream clang_iss(clang_line);

            string gcc_name, gcc_ns1, gcc_ns2;
            long int gcc_real_time, gcc_cpu_time, gcc_it;
            string clang_name, clang_ns1, clang_ns2;
            long int clang_real_time, clang_cpu_time, clang_it;

            if(!(gcc_iss >> gcc_name >> gcc_real_time >> gcc_ns1 >> gcc_cpu_time >> gcc_ns2 >> gcc_it)){break;}
            if(!(clang_iss >> clang_name >> clang_real_time >> clang_ns1 >> clang_cpu_time >> clang_ns2 >> clang_it)){break;}

            total_gcc_real_time = total_gcc_real_time + gcc_real_time;
            total_gcc_cpu_time = total_gcc_cpu_time + gcc_cpu_time;
            total_gcc_it = total_gcc_it + gcc_it;

            total_clang_real_time = total_clang_real_time + clang_real_time;
            total_clang_cpu_time = total_clang_cpu_time + clang_cpu_time;
            total_clang_it = total_clang_it + clang_it;

            if((gcc_real_time-clang_real_time) >= 0){
                nop_clang_dominant_real_time++;
            }

            if((gcc_cpu_time-clang_cpu_time) >= 0){
                nop_clang_dominant_cpu_time++;
            }

            if((gcc_it-clang_it) >= 0){
                nop_clang_dominant_it++;
            }

        }
    }

    std::cout<<std::left<<setw(16)<<"RT1"<<setw(16)<<"CPUT1"<<setw(16)<<"IT1"<<std::endl;
    std::cout<<"#1 "<<std::left<<setw(16)<<total_gcc_real_time<<setw(16)<<total_gcc_cpu_time<<setw(16)<<total_gcc_it <<"\n"
    <<"#1 "<<setw(16)<<(double)total_gcc_real_time/total_nop<<setw(16)<<(double)total_gcc_cpu_time/total_nop<<setw(16)<<(double)total_gcc_it/total_nop <<"\n"
    <<"#2 "<<setw(16)<<total_clang_real_time<<setw(16)<<total_clang_cpu_time<<setw(16)<<total_clang_it <<"\n"
    <<"#2 "<<setw(16)<<(double)total_clang_real_time/total_nop<<setw(16)<<(double)total_clang_cpu_time/total_nop<<setw(16)<<(double)total_clang_it/total_nop <<"\n"
    <<setw(16)<<(double)100*(total_gcc_real_time-total_clang_real_time)/total_gcc_real_time
    <<setw(16)<<(double)100*(total_gcc_cpu_time-total_clang_cpu_time)/total_gcc_cpu_time
    <<setw(16)<<(double)100*(total_gcc_it-total_clang_it)/total_gcc_it<<std::endl;


    std::cout<<"Total #ops: "<<total_nop<<std::endl;
    std::cout<<"#op 2nd one Dominant: "<<setw(16)<<nop_clang_dominant_real_time<<setw(16)<<nop_clang_dominant_cpu_time<<setw(16)<<nop_clang_dominant_it <<std::endl;
    std::cout<<"#op 1st one Dominant: "<<setw(16)<<total_nop-nop_clang_dominant_real_time<<setw(16)<<total_nop-nop_clang_dominant_cpu_time<<setw(16)<<total_nop-nop_clang_dominant_it <<std::endl;

}

void print_head(char *arg1, char *arg2){

    std::cout<<"\n\n==========================================================================================================================================="<<std::endl;
    std::cout<<"Comparison   "<<arg1<<"  vs  "<<arg2<<std::endl;
    //std::cout<<"==========================================================================================================================================="<<std::endl;
}

int main(int argc, char *argv[])
{
    print_head(argv[1],argv[2]);
    read_data(argv[1],argv[2]);

/*
    print_head(argv[1],argv[2]);
    one_vs_other(argv[1],argv[2]);


    print_head(argv[1],argv[2]);
    gate_gate_gcc_clang(argv[1],argv[2]);
*/
/*
    print_head(argv[3],argv[4]);
    one_vs_other(argv[3],argv[4]);

    print_head(argv[1],argv[3]);
    one_vs_other(argv[1],argv[3]);

    print_head(argv[2],argv[4]);
    one_vs_other(argv[2],argv[4]);
*/

    return 0;
}

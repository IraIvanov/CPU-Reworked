#include "cmd.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "../Stack/stack.hpp"
#include "cpu_lib.hpp"
#include <math.h>

#define CMD_BYTES 0x1F
#define ARG_BYTES 0
double const EPSILON = 0.00000001;

int is_equal(el_type var1, el_type var2) {

    if ( abs(var1 - var2) < EPSILON ) return 0;

    return 1;

}

int execute (char *code, size_t code_size, stack* stk, el_type* ram, size_t ram_size, el_type *regs ) {

    el_type var1 = 0, var2 = 0;
    int ip = 0;

    while ( ip < code_size && ip > 0) {
        switch (code[ip] & CMD_BYTES){
            case PUSH:

                el_type val = 0;
                if( code[ip] & 0x80 ){
                    if ( code[ip] & 0x40 ) {
                        ip++;
                        char arg = regs[code[ip++]];
                        val = ram[arg]; 
                    }
                    if (code[ip] & 0x20) {
                        ip++;
                        int arg = code[ip];
                        ip += sizeof(int);
                        val = ram[arg];
                    }
                }

                if ( code[ip] & 0x40 ) {
                        ip++;
                        val = regs[code[ip++]];
                }
                if (code[ip] & 0x20) {
                    ip++;
                    val = code[ip];
                    ip += sizeof(el_type);
                }

                stack_push(stk, val);
                printf("pushing[%lf]\n", val);
                break;
            case ADD:

                stack_pop(stk, &var1);
                stack_pop(stk, &var2);
                printf("add var1[%lf]  var2[%lf]\n", var1, var2);
                stack_push(stk, var1 + var2);
                ip++;
                break;
            case SUB:

                stack_pop(stk, &var1);
                stack_pop(stk, &var2);
                printf("sub var1[%lf]  var2[%lf]\n", var1, var2);
                stack_push(stk, var2 - var1);
                ip++;
                break;
            case MUL:
                
                stack_pop(stk, &var1);
                stack_pop(stk, &var2);
                printf("mul var1[%lf]  var2[%lf]\n", var1, var2);
                stack_push(stk, var1*var2);
                ip++;
                break;
            case DIV:

            stack_pop(stk, &var1);
            stack_pop(stk, &var2);
            if ( is_equal( var1, 0 ) ){
                printf("EXECUTING ERROR, DIVISION BY ZERO");
                return -1;
            }
            printf("div var1[%lf]  var2[%lf]\n", var1, var2);
            stack_push(stk, var2 / var1);
            ip++;
            case OUT:
                
                stack_pop(stk, &var1);
                printf("%lf\n", var1);
                ip++;
                break;
            case DUMP:

                printf("dumping...\n");
                //dump_cpu(code, ip);
                ip++;
                break;
            case HLT:
                
                stack_dtor(stk);
                printf("end of executing the programm\n");
                return 0;
                break;
            case JMP:
                ip = code[ip];
                break;
            case POP:
                
                stack_pop(stk, &var1);

                if( code[ip] & 0x80 ){
                    if ( code[ip] & 0x40 ) {
                        ip++;
                        char arg = regs[code[ip++]];
                        ram[arg] = var1; 
                    }
                    if (code[ip] & 0x20) {
                        ip++;
                        int arg = code[ip];
                        ip += sizeof(int);
                        ram[arg] = var1;
                    }
                }

                if ( code[ip] & 0x40 ) {
                        ip++;
                        regs[code[ip++]] = var1;
                }
                stack_push(stk, val);
                printf("pushing[%lf]\n", val);
                break;
            case DUP:
                stack_pop(stk, &var1);
                stack_push(stk, var1);
                stack_push(stk, var1);
                printf("duplicating &lf\n", var1);
                break;
            default:
                printf("UNKNOWN COMMAND\n");
                return -1;
                break;
        }
    }

    return 0;
}
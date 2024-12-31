package main

import {
    fmt;
    debug;
}

global {
    var int64[,,] global_int64_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 三维数组的初始化

@main
fn main() {
    global_int64_array_0 =  int64[,,]{
        int64[,]{
            int64[]{ 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L},
            int64[]{10L,11L,12L,13L,14L,15L,16L,17L,18L,19L},
            int64[]{20L,21L,22L,23L,24L,25L,26L,27L,28L,29L},
            int64[]{30L,31L,32L,33L,34L,35L,36L,37L,38L,39L},
            int64[]{40L,41L,42L,43L,44L,45L,46L,47L,48L,49L},
            int64[]{50L,51L,52L,53L,54L,55L,56L,57L,58L,59L},
            int64[]{60L,61L,62L,63L,64L,65L,66L,67L,68L,69L},
            int64[]{70L,71L,72L,73L,74L,75L,76L,77L,78L,79L},
            int64[]{80L,81L,82L,83L,84L,85L,86L,87L,88L,89L},
            int64[]{90L,91L,92L,93L,94L,95L,96L,97L,98L,99L}
        },
        int64[,]{
            int64[]{100L,101L,102L,103L,104L,105L,106L,107L,108L,109L},
            int64[]{110L,111L,112L,113L,114L,115L,116L,117L,118L,119L},
            int64[]{120L,121L,122L,123L,124L,125L,126L,127L,128L,129L},
            int64[]{130L,131L,132L,133L,134L,135L,136L,137L,138L,139L},
            int64[]{140L,141L,142L,143L,144L,145L,146L,147L,148L,149L},
            int64[]{150L,151L,152L,153L,154L,155L,156L,157L,158L,159L},
            int64[]{160L,161L,162L,163L,164L,165L,166L,167L,168L,169L},
            int64[]{170L,171L,172L,173L,174L,175L,176L,177L,178L,179L},
            int64[]{180L,181L,182L,183L,184L,185L,186L,187L,188L,189L},
            int64[]{190L,191L,192L,193L,194L,195L,196L,197L,198L,199L}
        },
        int64[,]{
            int64[]{200L,201L,202L,203L,204L,205L,206L,207L,208L,209L},
            int64[]{210L,211L,212L,213L,214L,215L,216L,217L,218L,219L},
            int64[]{220L,221L,222L,223L,224L,225L,226L,227L,228L,229L},
            int64[]{230L,231L,232L,233L,234L,235L,236L,237L,238L,239L},
            int64[]{240L,241L,242L,243L,244L,245L,246L,247L,248L,249L},
            int64[]{250L,251L,252L,253L,254L,255L,256L,257L,258L,259L},
            int64[]{260L,261L,262L,263L,264L,265L,266L,267L,268L,269L},
            int64[]{270L,271L,272L,273L,274L,275L,276L,277L,278L,279L},
            int64[]{280L,281L,282L,283L,284L,285L,286L,287L,288L,289L},
            int64[]{290L,291L,292L,293L,294L,295L,296L,297L,298L,299L}
        }
    };

    


    fmt::println_string("test cast 1 ------------------------");
    debug::assert(len(global_int64_array_0)    == 3);
    debug::assert(len(global_int64_array_0[0]) == 10);
    debug::assert(len(global_int64_array_0[1]) == 10);
    debug::assert(len(global_int64_array_0[2]) == 10);

    debug::assert(len(global_int64_array_0[0,0]) == 10);
    debug::assert(len(global_int64_array_0[1,9]) == 10);
    debug::assert(len(global_int64_array_0[2,9]) == 10);



    var int i;
    var int j;
    var int k;
    var int num;

    fmt::println_string("\ntest cast 2 ------------------------");

    for(i=0; i<len(global_int64_array_0); i=i+1) {
        for(j=0; j<len(global_int64_array_0[i]); j=j+1) {
            for(k=0; k<len(global_int64_array_0[i,j]); k=k+1) {
                if(global_int64_array_0[i,j,k] != to_int64(i*100+j*10+k)) {
                    fmt::println_string("test failed1");
                }
                if(global_int64_array_0[i,j,k] != to_int64(num)) {
                    fmt::println_string("test failed2");
                }
                num++;
            } 
        }
    }

    debug::assert(num == 300);

}

pgc++ main.cpp -ta=nvidia -Minfo=accel -o main
nsys profile -o name -t cuda,openacc -y NN -d NN ./main 
-y delay
-d duration

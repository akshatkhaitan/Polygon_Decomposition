
echo "Welcome to our DAA Bash Runner"
# for n in 500
# do
#     mkdir $n
#     python3 polygon_generator.py $n
#     g++ main.cpp
#     ./a.out
#     python3 python_visualizer_before.py $n
#     python3 python_visualizer_after.py $n
#     python3 plot_time.py $n
# done

n=59
mkdir hand
# python3 polygon_generator.py $n
g++ main.cpp
./a.out
python3 python_visualizer_before.py $n 
python3 python_visualizer_after.py $n
python3 plot_time.py $n

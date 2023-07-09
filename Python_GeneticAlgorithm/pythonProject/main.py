import math

import numpy as np
import random
from tkinter import *
# import matplotlib.pyplot as plt


class Population:
    def __init__(self, number_of_chromosomes, number_of_chromosomes_parts):
        self.chromosomes = [Chromosome(number_of_chromosomes_parts, None, None) for _ in range(number_of_chromosomes)]

    def create_new_population(self, chromosomes):
        self.chromosomes = chromosomes

    def generate_population(self, prob_gen, probability_fitting):
        new_chromosomes = []
        for main_probability in prob_gen:
            sum_of_prob = 0
            for fitting_probability in probability_fitting:
                sum_of_prob += fitting_probability
                if main_probability < sum_of_prob:
                    tested_values = np.where(probability_fitting == fitting_probability)
                    correct_values = np.array(tested_values).tolist()
                    if not isinstance(correct_values, int):
                        if len(correct_values) > 1:
                            result = correct_values[1]
                        else:
                            result = correct_values
                    for z in range(6):
                        if isinstance(result,
                                      int):
                            if z == result:
                                new_chromosomes.append(self.chromosomes[z])
                                break
                        else:
                            if z == result[0][0]:
                                new_chromosomes.append(self.chromosomes[z])
                                break
                        z += 1
                    break
        return new_chromosomes


class Chromosome:

    def __init__(self, length, x1, y1):
        if x1 is None:
            self.numbers = np.random.randint(-10, 10, length)  # range from -10 to 10 of first population
        else:
            self.numbers = np.array([x1, y1])

        self.length = length


def count_function(a, b, c):
    return a ** 2 + b + c


def fitness_function(chromosome, c):
    return count_function(chromosome.numbers[0], chromosome.numbers[1], c)


def binary(binary_number):
    i = 0
    arrayOfBinary = []
    # negative
    if binary_number < 0:
        binary_number = -1 * binary_number
        arrayOfBinary.insert(0, 1)
    else:
        arrayOfBinary.insert(0, 0)
    while binary_number > 0:
        arrayOfBinary.append(binary_number % 2)
        binary_number = binary_number // 2
        i = i + 1

    return arrayOfBinary


def list_to_string(s):
    str1 = ""
    for ele in s:
        str1 += str(ele)
    return str1


def crossover(first_chromosome, second_chromosome):

    first_chromosome = list(first_chromosome)
    second_chromosome = list(second_chromosome)

    k = random.randint(0, 21)  # from 0 to 21 because 2*11 = 22

    for r in range(k, 21):
        first_chromosome[r], second_chromosome[r] = second_chromosome[r], first_chromosome[r]
    first_chromosome = ''.join(first_chromosome)
    second_chromosome = ''.join(second_chromosome)

    return first_chromosome, second_chromosome


def mutation(string_of_data, probability):
    for g in range(len(string_of_data)):
        if np.random.rand() < probability:
            string_of_data[g] = str(1 - int(string_of_data[g]))
    return string_of_data


def connect(population):
    binary_population = []

    for i in range(6):
        first = binary(population.chromosomes[i].numbers[0])
        second = binary(population.chromosomes[i].numbers[1])
        while len(first) != 11:
            first.insert(1, 0)
        while len(second) != 11:
            second.insert(1, 0)
        z = first + second
        binary_population.insert(i, z)
    return binary_population


def new_gen(population, c):
    fittings = []
    probability_fitting = []
    for chromosome in population.chromosomes:
        fitness = fitness_function(chromosome, c)
        if fitness != 0:
            fittings.append(1 / fitness)
        else:
            fittings.append(0)

    for fitting in fittings:
        probability_fitting.append(fitting / sum(fittings))

    prob_gen = np.random.uniform(0, 1, 6)
    chromosomes_to_add = population.generate_population(prob_gen, probability_fitting)
    for _ in population.chromosomes:
        del population.chromosomes[0]
    population.chromosomes = []
    population.create_new_population(chromosomes_to_add)
    for _ in fittings:
        del fittings[0]
    del prob_gen
    del probability_fitting
    del fittings
    return population


def crossover_this(binary_p):
    results = []
    for d in range(3):
        results.append(crossover(list_to_string(binary_p[2 * d]), list_to_string(binary_p[2 * d + 1])))
    return results


def mutation_this(results):
    new_results = []
    for m in range(3):
        for j in range(2):
            new_m = list(results[m][j])
            new_results.append(mutation(new_m, 0.045))
    return new_results


def back_to_correct_format(new_results):
    split_strings = []
    s_results = []

    for i in range(6):
        chromosomes_string = ''.join(new_results[i])
        s_results.append(chromosomes_string)

    for i in range(6):
        for index in range(0, 22, 11):  # from 0 to 22 by 11
            split_strings.append(s_results[i][index: index + 11])

    int_results = []

    chromosomes_string = list(split_strings)
    for i in range(12):
        if_negative = chromosomes_string[i][0]
        if if_negative == '0':
            if_negative = 1
        else:
            if_negative = -1
        temp = chromosomes_string[i][1:]
        int_results.append(if_negative * int(temp, 2))
    return int_results


def genetic_algorithm(c):
    # first population
    population = Population(6, 2)
    c = int(c)
    closest_number = math.inf
    closest_a = 0
    closest_b = 0

    for y2 in range(10000):
        population = new_gen(population, c)
        # print("After creating new generation")
        # for b in range(6):
        #     print(population.chromosomes[b].numbers)
        binary_population = connect(population)
        results = crossover_this(binary_population)
        new_results = mutation_this(results)
        int_results = back_to_correct_format(new_results)
        for j in range(6):
            current_number = int_results[j * 2] * int_results[j * 2] + int_results[j * 2 + 1] + c
            if abs(current_number) < abs(closest_number):
                closest_number = current_number
                closest_a = int_results[j * 2]
                closest_b = int_results[j * 2 + 1]
        if count_function(closest_a, closest_b, c) == 0:
            break

        for k in range(6):
            del population.chromosomes[0]
        # print("After mutation and crossover")
        for e in range(6):
            population.chromosomes.append(Chromosome(2, int_results[e * 2], int_results[e * 2 + 1]))
        # print(population.chromosomes[e].numbers)

    #  print("A=")
    # print(closest_a)
    #  print("B=")
    # print(closest_b)
    #  print("C=")
    # print(c)
    #  print("Delta=")
    # print(count_function(closest_a, closest_b, c))
    del population
    result_a = "a=" + str(closest_a)
    result_b = "b=" + str(closest_b)
    result_c = "c=" + str(c)
    delta = "Delta=" + str(count_function(closest_a, closest_b, c))
    number_of_generations = "Gens=" + str(y2+1)
    # save c and delta to file
    f = open("results.txt", "a")
    f.write(str(c))
    f.write(str(delta) + "\n")
    f.close()

    return [result_a, result_b, result_c, delta, number_of_generations]


class Window:

    def __init__(self, window_root):
        self.top = Label(window_root, text="Enter c")
        self.top.pack()

        self.f = Label(window_root, text="a^2 + b + c = 0", bg="white", fg="black")
        self.f.pack()

        self.e = Entry(window_root)
        self.e.pack()
        self.e.focus_set()

        self.b = Button(window_root, text="Count", command=self.check_expression)
        self.b.pack()

        self.answer = StringVar()
        self.answer.set("Results:")

        self.check = Label(window_root, text=self.answer.get(), textvariable=self.answer)
        self.check.pack()

    def check_expression(self):
        data = self.e.get()
        if data != "":
            if (data[0] == '-' and data[1:].isdigit()) or data.isdigit():
                self.answer.set(genetic_algorithm(data))


# draw a graph
# file1 = open('results.txt', 'r')
# Lines = file1.readlines()

# count = 0
# c_plot = []
# delta_plot = []
# for line in Lines:
    # count += 1
    # line = line.split("Delta=")
    # line[1] = line[1][0:-1]
    # c_plot.append(line[0])
    # delta_plot.append(line[1])

# plt.plot(c_plot, delta_plot)
# plt.xlabel('Value of c')
# plt.ylabel('Delta value')
# plt.title('Graph c/delta')
# plt.savefig('Graph.png')

root = Tk()
w = Window(root)
root.title("Check numbers")
root.geometry("300x150")
root.mainloop()

package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"sync"
	"strconv"
	"time"
)

type Objeto struct {
	ID    int
	Total int
	Grupo int
}

func NewObjeto(id int) Objeto {
	return Objeto{
		ID:    id,
		Total: rand.Intn(11),
		Grupo: rand.Intn(5) + 1,
	}
}

func main() {
	N, _ := strconv.Atoi(os.Args[1])
	T, _ := strconv.Atoi(os.Args[2])
	base10N := int(math.Pow(10, float64(N)))
	totais := 0
	totaisGrupo := [5]int{0}
	somas := [264]int{0}
	somasGrupo := make([][]int, 264)
	listaMenor := make([][]int, 264)
	listaMaior := make([][]int, 264)
	
	for i := range somasGrupo {
		somasGrupo[i] = make([]int, 5)
	}

	rand.Seed(27600)

	lista := make([]Objeto, base10N)

	for i := 0; i < base10N; i++ {
		lista[i] = NewObjeto(i)
	}

	teto := float64(base10N) / float64(T)

	var wg sync.WaitGroup
	
	start := time.Now()
	//// Processamento
	for i := 0; i < T; i++ {
		wg.Add(1)
		i := i
		go func () {
			defer wg.Done()
			inicio := int(math.Ceil(teto * float64(i)))
			fim := int(math.Ceil(teto * float64(i+1)))
					
			for j := inicio; j < fim; j++ {
				somas[i] += lista[j].Total
				somasGrupo[i][lista[j].Grupo-1] += lista[j].Total

				if lista[j].Total < 5 {
					listaMenor[i] = append(listaMenor[i], lista[j].ID)
							
				} else {
						listaMaior[i] = append(listaMaior[i], lista[j].ID)
				}
			}
		}()
	}
	wg.Wait()
	

	
	for i := 0; i < T; i++ {
		totais += somas[i]
		for j := 0; j < 5; j++ {
			totaisGrupo[j] += somasGrupo[i][j]
		}
	}

	finalMenorList := make([]int, 0)
	finalMaiorList := make([]int, 0)

	for i := 0; i < T; i++ {
		finalMenorList = append(finalMenorList, listaMenor[i]...)
		finalMaiorList = append(finalMaiorList, listaMaior[i]...)
	}
	/// Processamento
	elapsed := time.Since(start)
	fmt.Println("N =", N)
	fmt.Println("T =", T)
    	fmt.Println("Tempo de execucao:", elapsed)
	
	
	fmt.Println("Total:", totais)
	fmt.Println("Totais grupo:")

	for i := 0; i < 5; i++ {
		fmt.Println(totaisGrupo[i])
	}

	fmt.Println("Quantidade menores que 5:", len(finalMenorList))
	fmt.Println("Quantidade maiores que 5:", len(finalMaiorList))
}


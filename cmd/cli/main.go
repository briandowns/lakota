package main

import (
	"flag"
	"fmt"
	"os"

	"github.com/briandowns/lakota"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Printf("usage: %s -h or --help\n", os.Args[0])
		os.Exit(1)
	}

	lakotaFlag := flag.String("l", "", "English translation of the given Lakota word")
	pronunciationFlag := flag.String("p", "", "Pronunciation for the given Lakota word")
	flag.Parse()

	switch {
	case lakotaFlag != nil && *lakotaFlag != "":
		for _, word := range lakota.Words {
			if *lakotaFlag == word.Lakota {
				fmt.Println(word.English)
			}
		}
	case pronunciationFlag != nil && *pronunciationFlag != "":
		for _, word := range lakota.Words {
			if *pronunciationFlag == word.Lakota {
				fmt.Println(word.Pronunciation)
			}
		}
	default:
		for _, word := range lakota.Words {
			if os.Args[1] == word.English {
				fmt.Printf("%s (%s)\n", word.Lakota, word.Pronunciation)
			}
		}
	}

	os.Exit(0)
}

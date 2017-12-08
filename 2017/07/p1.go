package main

import (
  "fmt"
  "strings"
)

type node struct {
  name string
  weight int
  parent *node
  children []*node
}

var nodes map[string]*node

func getOrCreate(name string, weight int, parent *node) *node {
  if nodes[name] != nil {
    if (weight != -1) {
      nodes[name].weight = weight
    }
    if (parent != nil) {
      nodes[name].parent = parent
    }
  } else {
    n := node{name: name, weight: weight, parent: parent}
    nodes[name] = &n
  }

  return nodes[name]
}

func main() {
  var name string
  var child string
  var weight int

  nodes = make(map[string]*node)

  for {
    child = ""
    i, _ := fmt.Scanf("%s (%d)->%v\n", &name, &weight, &child)

    if i == 0 {
      break
    }

    n := getOrCreate(name, weight, nil)

    if child != "" {
      for _, childName := range strings.Split(child, ",") {
        c := getOrCreate(childName, -1, n);
        n.children = append(n.children, c)
      }
    }
  }

  for _, n := range nodes {
    if (n.parent == nil) {
      fmt.Printf("Part 1: %v\n", n.name)
    }
  }

}

package main

import (
  "fmt"
  "strings"
  "math"
  "os"
)

type node struct {
  name string
  weight int
  parent *node
  children []*node
  totalWeight int
}

var nodes map[string]*node

func getOrCreate(name string, weight int, parent *node) *node {
  if nodes[name] != nil {
    if (weight != -1) {
      nodes[name].weight = weight
      nodes[name].totalWeight = weight
    }
    if (parent != nil) {
      nodes[name].parent = parent
    }
  } else {
    n := node{name: name, weight: weight, parent: parent, totalWeight: weight}
    nodes[name] = &n
  }

  return nodes[name]
}

func getDiffValue(s []int) int {
  m := make(map[int]int)
  for _, i := range s {
    m[i]++
  }

  for k, v := range m {
    if (v == 1) {
      return k
    }
  }

  return -1
}

func updateTreeWeights(n *node) int {
  for _, c := range n.children {
    n.totalWeight += updateTreeWeights(c)
  }

  return n.totalWeight
}

func getWrongDisc(n *node) int {
  s := []int{}
  for _, c := range n.children {
    s = append(s, c.totalWeight)
  }

  diff := getDiffValue(s)

  if (diff == -1) {
    return 0
  }

  for i, c := range n.children {
    if (c.totalWeight == diff) {
      getWrongDisc(c)
      var ci *node
      if (i == 0) {
        ci = n.children[1]
      } else {
        ci = n.children[0]
      }
      fmt.Println(c.weight - int(math.Abs(float64(ci.totalWeight - c.totalWeight))))
      os.Exit(0)
    }
  }

  return 0
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

  var root *node
  for _, n := range nodes {
    if (n.parent == nil) {
      root = n
      break
    }
  }

  updateTreeWeights(root)
  getWrongDisc(root)
}

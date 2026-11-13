
public void main(String[] args) {
    //p1
    List<String> words =Arrays.asList("hi","hello","buna");
    words.stream().forEach(s->System.out.println("  "+s));

    //p2
    words.stream().forEach(System.out::println);

    //p3
    List<String> excitingwords = words.stream().map(s->s+"!").toList();

    List<String> eyewords = words.stream().map(s->s.replace(",","eye")).toList();

    List<String> upperCaseWords  =  words.stream().map(s->s.toUpperCase()).toList();

    //p4
    List<String> shortWords = words.stream().filter(s->s.length()<4).toList();
    List<String> wordsWithB = words.stream().filter(s->s.contains("b")).toList();
    List<String> evenLength = words.stream().filter(s->s.length()%2==0).toList();

    //p5
    System.out.println(p5())
}

Optional<String> p5(List<String> words){
    return words.stream().map(String::toUpperCase).
            filter(s->s.length()<4).
            filter(s->s.contains("b")).
            findFirst();
}

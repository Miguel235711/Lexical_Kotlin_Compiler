val words = listOf("Lets", "find", "something", "in", "collection", "somehow")  // 1

val first = words.find { it.startsWith("some") }                                // 2
val last = words.findLast { it.startsWith("some") }                             // 3

val nothing = words.find { it.contains("nothing") }                             // 4
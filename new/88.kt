val result = html {                                            // 1
    head {                                                     // 2
        title { +"HTML encoding with Kotlin" }
    }
    body {                                                     // 2
        h1 { +"HTML encoding with Kotlin" }
        p {
            +"this format can be used as an"                   // 3
            +"alternative markup to HTML"                      // 3
        }

        // an element with attributes and text content
        a(href = "http://kotlinlang.org") { +"Kotlin" }

        // mixed content
        p {
            +"This is some"
            b { +"mixed" }
            +"text. For more see the"
            a(href = "http://kotlinlang.org") {
                +"Kotlin"
            }
            +"project"
        }
        p {
            +"some text"
            ul {
                for (i in 1..5)
                li { +"${i}*2 = ${i*2}" }
            }
        }
    }
}

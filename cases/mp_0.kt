package mx.tec.fooddelivery

import android.app.Application
import com.stripe.android.PaymentConfiguration

class App : Application() {
    override fun onCreate() {
        super.onCreate()
        PaymentConfiguration.init(
            applicationContext,
            "pk_test_51HozMhBTmRP6NlfkK3SB4It2V0XxEgpV8lqoYFqOvWqACI5cGLjZH6b9KpMlc2oQKtHwGxcWyGb0dlEIQy9gVkmj00YmdXH4sO"
        )
    }
}
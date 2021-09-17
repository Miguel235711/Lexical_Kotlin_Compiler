package mx.tec.fooddelivery
import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import androidx.annotation.RequiresApi
import com.google.android.material.navigation.NavigationView
import androidx.navigation.findNavController
import androidx.drawerlayout.widget.DrawerLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import androidx.core.view.GravityCompat
import androidx.core.view.get
import androidx.core.view.isVisible
import androidx.core.view.size
import androidx.navigation.NavController
import androidx.navigation.ui.*
import com.bumptech.glide.Glide
import com.google.android.material.bottomnavigation.BottomNavigationView
import com.google.firebase.ktx.Firebase
import kotlinx.android.synthetic.main.activity_main.*
import mx.tec.fooddelivery.services.auth.AuthService
import mx.tec.fooddelivery.services.product.ProductModel
import mx.tec.fooddelivery.ui.shared.user.EditUserInfoActivity
import mx.tec.fooddelivery.ui.ui.auth.AuthScreen
import com.google.firebase.storage.ktx.storage
import com.google.mlkit.common.model.DownloadConditions
import com.google.mlkit.common.model.RemoteModelManager
import com.google.mlkit.vision.label.automl.AutoMLImageLabelerRemoteModel
import com.stripe.android.CustomerSession
import kotlinx.android.synthetic.main.product_item.*
import mx.tec.fooddelivery.services.payment.CustomEphemeralKeyProvider

class HomeScreen : AppCompatActivity(),NavigationView.OnNavigationItemSelectedListener {
    //TODO
    private lateinit var appBarConfiguration: AppBarConfiguration
    private lateinit var drawerLayout: DrawerLayout
    private lateinit var bottomNavView: BottomNavigationView
    private lateinit var bottomNavigationViewMenu: Menu
    private lateinit var navController: NavController
    private lateinit var authServiceInstance: AuthService
    private lateinit var usernameView : TextView
    private lateinit var emailView: TextView
    private lateinit var adminView : TextView
    private lateinit var userProfileImageView: ImageView
    private val storage = Firebase.storage.reference
    private val TAG = "HomeScreen"
    @RequiresApi(Build.VERSION_CODES.O)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val toolbar: Toolbar = findViewById(R.id.toolbar)
        setSupportActionBar(toolbar)

        drawerLayout = findViewById(R.id.drawer_layout)
        val navView = findViewById<NavigationView>(R.id.nav_view)
        authServiceInstance = AuthService.getInstance(this)
        authServiceInstance.getCurrentUserData().observe(this){
            if(it.isNotEmpty()) {
                if (!authServiceInstance.isAdmin()) {
                    navView.menu.findItem(R.id.nav_consumer_orders).isVisible = false
                }
            }
        }
        val header = navView.getHeaderView(0)
        usernameView =  header.findViewById(R.id.textViewdrawerUsername)
        emailView = header.findViewById(R.id.textViewdrawerMail)
        adminView = header.findViewById(R.id.textViewdrawerAdmin)
        userProfileImageView = header.findViewById(R.id.imageViewProfileDrawer)
        navController = findNavController(R.id.nav_host_fragment)
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        appBarConfiguration = AppBarConfiguration(setOf(R.id.action_home,R.id.action_menu,R.id.action_current_order,R.id.action_history,R.id.nav_payment_method,R.id.nav_consumer_orders), drawerLayout)
        setupActionBarWithNavController(navController, appBarConfiguration)
        navView.setupWithNavController(navController)
        bottomNavView = findViewById<BottomNavigationView>(R.id.bottom_navigation_view)
        bottomNavigationViewMenu = bottomNavView.menu
        bottomNavView.setupWithNavController(navController)
        nav_logout.setOnClickListener{
            authServiceInstance.logout(){
                val intent = Intent(applicationContext,AuthScreen::class.java)
                startActivity(intent)
                finish()
            }
        }
        navView.setNavigationItemSelectedListener(this)
        ///botoom navagation view
        /*val bottomNavigationView = findViewById<BottomNavigationView>(R.id.bottom_navigation_view)
        bottomNavigationView.setOnNavigationItemSelectedListener {
            supportFragmentManager.beginTransaction()
                .replace(R.id.nav_host_fragment,
                    when(it.itemId){
                        R.id.action_menu->MenuFragment()
                        R.id.action_current_order->CurrentOrderFragment()
                        R.id.action_history->HistoryFragment()
                        else->HomeFragment()
                    }
                ).commit()
            return@setOnNavigationItemSelectedListener true
        }*/
        //customer session
        Log.d(TAG,"customer id: ${authServiceInstance.getCurrentUserId()!!}")
        CustomerSession.initCustomerSession(
            this,
            CustomEphemeralKeyProvider(authServiceInstance.getCurrentUserId()!!)
        )
        header.setOnClickListener{
            Log.d(TAG,"header clicked")
            val editUserInfo = Intent(this,EditUserInfoActivity::class.java)
            startActivity(editUserInfo)
        }
        //navView.setNavigationItemSelectedListener(this)
    }
    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    @RequiresApi(Build.VERSION_CODES.O)
    override fun onResume() {
        super.onResume()
        Log.d(TAG,"onResume")
        authServiceInstance.getCurrentUserData().observe(this){
            //change drawer elements
            if(it.isNotEmpty()) {
                val user = it[0]
                Log.d(TAG,"user displayname: ${user.displayname}")
                usernameView.text = user.displayname
                emailView.text = user.email
                adminView.isVisible = user.isAdmin
                //download image uri
                Log.d(TAG,"going to download the image uri of ${it[0].profileImageDir}")
                if(it[0].profileImageDir.isNotBlank()){
                    storage.child(it[0].profileImageDir).downloadUrl.addOnSuccessListener { uri ->
                        //download image and set with glide
                        Log.d(TAG, "uri of profile image: $uri")
                        Glide.with(this)
                            .load(uri)
                            .dontTransform()
                            /*.apply(
                                RequestOptions()
                                    .fitCenter()
                                    //.override(imageView!!.width*3,imageView!!.height*3)
                            )*/
                            .into(userProfileImageView)
                    }
                }
            }
        }
    }
    override fun onSupportNavigateUp(): Boolean {
        val navController = findNavController(R.id.nav_host_fragment)
        return navController.navigateUp(appBarConfiguration) || super.onSupportNavigateUp()
    }
    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        Log.d(TAG,"onNavigationItemSelected of drawer is being called and itemId id is ${item.itemId}")
        val bottomNavigationViewMenu = bottomNavView.menu
        //unckeck all items of bottom navigationView
        bottomNavigationViewMenu.setGroupCheckable(0,true,false)
        for(i in 0 until bottomNavigationViewMenu.size) {
            //Log.d(tag,"bottomNavView child: ${bottomNavigationViewMenu.get(i)}")
            bottomNavigationViewMenu.getItem(i).isChecked=false
            //(bottomNavView.get(i) as MenuItem).isChecked = false
        }
        bottomNavigationViewMenu.setGroupCheckable(0,true,true)
        drawerLayout.closeDrawer(GravityCompat.START)

        return NavigationUI.onNavDestinationSelected(item,navController)
    }
}
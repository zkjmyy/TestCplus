#include <jni.h>
#include <string>
#include<android/log.h>
#include <string.h>
#include<stdio.h>


#define  LOG_TAG   "native-lib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型


//返回两个字符串相加
extern "C"
JNIEXPORT jstring JNICALL
Java_com_gxsn_testcplus_MainActivity_stringFromJNI(JNIEnv* env,jobject jobject,jstring a ,jstring b) {
    std::string hello = "Hello from C++" ;

//    char* cstr = Jstring2CStr(env,a);
//    char* cstr1 = Jstring2CStr(env,b);
//
//
//
//    char* cc = strcat(cstr,cstr1); //拼接两个字符串
    return env->NewStringUTF(hello.c_str());
}

//
//char*   Jstring2CStr(JNIEnv*   env,   jstring   jstr)
//{
//  char*   rtn   =   NULL;
//  jclass   clsstring   =   (*env)->FindClass(env,"java/lang/String");    //找到string的class
//  jstring   strencode   =   (*env)->NewStringUTF(env,"GB2312");     //得到一个java字符串"GB2312"
//  jmethodID   mid   =   (*env)->GetMethodID(env,clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
//   //从String类包找到名为"getBytes"的方法，这个方法的签名：（参数）返回值，参数：String 返回值：[B   bytes类型的数组
//  jbyteArray   barr=   (jbyteArray)(*env)->CallObjectMethod(env,jstr,mid,strencode); // String .getByte("GB2312");
//    //参数1,：env，参数二：要转换的字符串，参数三：上面取得的函数ID，参数四：要转换的数据类型。转换成Byte数组
//  jsize   alen   =   (*env)->GetArrayLength(env,barr);        //得到数组的长度
//  jbyte*   ba   =   (*env)->GetByteArrayElements(env,barr,JNI_FALSE);        //获取byte数组中的每一个元素，并放入一个内存空间里
//  if(alen   >   0)
//  {
//   rtn   =   (char*)malloc(alen+1);         //"\0"   申请一块内存空间，这块内存空间的大小为：alen+1既多加一个“\0”的长度
//   memcpy(rtn,ba,alen);                       //将ba里面的内容拷贝到char * rtn这个指针所指的内存里
//   rtn[alen]=0;                                       //把rtn数组里的最后一个元素赋值为0
//  }
//  (*env)->ReleaseByteArrayElements(env,barr,ba,alen+1);
//  //释放ByteArray数组所占的空间  JNIenv   env , jinArray barr ba(刚才申请的空间赋给了谁)  alen+1数组的长度
//  return rtn;                                            //返回char * rtn的指针 地址
//}




//返回整数值
extern "C"
JNIEXPORT jint JNICALL
Java_com_gxsn_testcplus_MainActivity_intfromJni(JNIEnv* env,jobject /* this */){
        int a = 1;
        int b = 5;
        int size = sizeof(char);
       return size;
}


//返回string 的数组
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_gxsn_testcplus_MainActivity_charfromJni(JNIEnv* env,jobject /* this */){

        jstring str;
        jobjectArray args = 0;
        jsize len = 5;
        const char* sa[] = { "Hello", "world!", "mx2", "is", "good" };
        int i = 0;
        args = (env)->NewObjectArray(len, (env)->FindClass("java/lang/String"), 0);
        for (i = 0; i < len; i++){
        str = (env)->NewStringUTF(sa[i]);
             (env)->SetObjectArrayElement(args, i, str);
        }

       return args;
}



//返回对象
extern "C"
JNIEXPORT jobject JNICALL
Java_com_gxsn_testcplus_MainActivity_objectformc(JNIEnv* env,jobject /* this */){
    //获取Java中的person类
    jclass objectClass = (env)->FindClass("com/gxsn/testcplus/model/Person");
    //得到这个类的构造方法id. //得到类的默认构造方法的id.都这样写.
    jmethodID consID = (env)->GetMethodID(objectClass, "<init>", "()V");
    //获取类中每一个变量的定义
    //name
    jfieldID str = (env)->GetFieldID(objectClass, "name", "Ljava/lang/String;");
    //年龄
    jfieldID strjob = (env)->GetFieldID(objectClass, "job", "Ljava/lang/String;");
    //index
    jfieldID age = (env)->GetFieldID(objectClass, "age", "I");
    //创建一个jobject对象.
    jobject myReturn = (env)->NewObject(objectClass, consID);


    //给每一个实例的变量赋值
    (env)->SetObjectField(myReturn, str, (env)->NewStringUTF("小熊。。。"));
    env ->SetObjectField(myReturn,strjob,env->NewStringUTF("哈哈哈,小样。。。赶快搬砖"));
    (env)->SetIntField(myReturn, age, 23);
    return myReturn;
}



//返回obj的对象的数组
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_gxsn_testcplus_MainActivity_objectsArray(JNIEnv *env, jobject _obj){

        jobjectArray MXArray = NULL; // jobjectArray 为指针类型
        jclass clsMX = NULL; // jclass 为指针类型
        jobject obj;
        jint len = 5; //设置这个数组的长度.
        //知道要返回的class.
        clsMX = env->FindClass("com/gxsn/testcplus/model/Person");
        //创建一个MXAray的数组对象.
        MXArray = env->NewObjectArray(len, clsMX, NULL);
        //获取类中每一个变量的定义
        //name
        jfieldID str = (env)->GetFieldID(clsMX, "name", "Ljava/lang/String;");
        //job
        jfieldID job = (env)->GetFieldID(clsMX, "job", "Ljava/lang/String;");
        //index
        jfieldID age = (env)->GetFieldID(clsMX, "age", "I");
        //得到这个类的构造方法id. //得到类的默认构造方法的id.都这样写.
        jmethodID consID = (env)->GetMethodID(clsMX, "<init>", "()V");
        for (jint i = 0; i < len; i++)
        {
        obj = env->NewObject(clsMX, consID);
        env->SetObjectField(obj, str, env->NewStringUTF("小熊。。。。"));
        env->SetObjectField(obj, job, env->NewStringUTF("oh,dear, Please move brick"));
        env->SetIntField(obj, age, (jint) i);
        env->SetObjectArrayElement(MXArray, i, obj);
        }
        return MXArray;
}



//java 中传递过来的读一下
extern "C"
JNIEXPORT void JNICALL

Java_com_gxsn_testcplus_MainActivity_movetoNaive(JNIEnv *env, jobject obj,jobject person){

  jclass man = env->GetObjectClass(person); //或得Student类引用

    if(man == NULL)
    {
        LOGD ("GetObjectClass failed \n")  ;
    }
    //下面这些函数操作，我们都见过的。O(∩_∩)O~
    jfieldID ageFieldID = env->GetFieldID(man,"age","I"); //获得得Student类的属性id
    jfieldID nameFieldID = env->GetFieldID(man,"name","Ljava/lang/String;"); // 获得属性ID
    jfieldID jobFieldID = env->GetFieldID(man,"job","Ljava/lang/String;"); // 获得属性ID

    jint age = (jint)env->GetIntField(man , ageFieldID);  //获得属性值
    jstring name = (jstring)env->GetObjectField(man , nameFieldID);//获得属性值
    jstring job = (jstring)env->GetObjectField(man , jobFieldID);//获得属性值

    const char * c_name = env->GetStringUTFChars(name ,NULL);//转换成 char *

//    string str_name = c_name ;
//    env->ReleaseStringUTFChars(name,c_name); //释放引用

//    cout << " at Native age is :" << age << " # name is " << str_name << endl ;


//            LOGE("sdfafsfsfasdsdf");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_gxsn_testcplus_MainActivity_movetonativeArray(JNIEnv *env, jobject obj,jobjectArray personarray,jint length){
    jint size = env->GetArrayLength(personarray);

    if(size > 0){

        for(jint i = 0;i < size ;i++ ){


           jobject obj =  env->GetObjectArrayElement(personarray,i);

           jclass man = env->GetObjectClass(obj); //或得Student类引用

           if(man == NULL)
           {
               LOGD ("GetObjectClass failed \n")  ;
           }
           //下面这些函数操作，我们都见过的。O(∩_∩)O~
           jfieldID ageFieldID = env->GetFieldID(man,"age","I"); //获得得Student类的属性id
           jfieldID nameFieldID = env->GetFieldID(man,"name","Ljava/lang/String;"); // 获得属性ID
           jfieldID jobFieldID = env->GetFieldID(man,"job","Ljava/lang/String;"); // 获得属性ID

           jint age = env->GetIntField(man , ageFieldID);  //获得属性值
           jstring name = (jstring)env->GetObjectField(man , nameFieldID);//获得属性值
           jstring job = (jstring)env->GetObjectField(man , jobFieldID);//获得属性值

           const char * c_name = env->GetStringUTFChars(name ,NULL);//转换成 char *

        }
    }
}









/*
创建调用的方法数组.    { "displayParms", "(Ljava/lang/String;IZ)V", (void*)jni_displayParms },java里面调用的方法 , (java调用时传入的参数类型)返回的类型 , 对应的jni里面的函数.
*/



//static JNINativeMethod const gMethods[] = {
////        { "displayParms", "(Ljava/lang/String;IZ)V", (void*)jni_displayParms },
////        { "add", "(II)I", (void*)jni_add },
////        { "setArray", "([Z)V",(void*)jni_setArray },
////        { "getStringArray", "()[Ljava/lang/String;",(void*) jni_getStringArray },
//        { "objectformc", "()Lcom/gxsn/testcplus/model/Person;",(void*) Java_com_gxsn_testcplus_MainActivity_objectformc },
//        { "objectsArray", "()[Lcom/gxsn/testcplus/model/Person;",(void*) Java_com_gxsn_testcplus_MainActivity_objectsArray },
//    };
////
////
////
//    /*
//    jni_Onload方法.照着写就行了.
//    */
//extern "C"
//JNIEXPORT jint JNICALL
//Java_com_gxsn_testcplus_MainActivity_onLoad(JavaVM *jvm, void *reserved) {
//        JNIEnv* env = NULL;
//        if (jvm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
//        {
//        return -1;
//        }
//        jclass clazz = (env)->FindClass("com/gxsn/testcplus/MainActivity"); //这里是唯一的要注意的. 这里的mx2是在java中引用jni类的类名.
//        (env)->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
//        return JNI_VERSION_1_4;
//        }
//        void JNI_OnUnload(JavaVM *jvm, void *reserved)
//        {
//        return;
//}




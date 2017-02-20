class Singleton_Meyer{
	public:
		Singleton_Meyer(const Singleton_Meyer&) = delete;
                Singleton_Meyer &operator=(const Singleton_Meyer&) = delete;
                Singleton_Meyer(Singleton_Meyer&& ) = delete;
                Singleton_Meyer &operator=(Singleton_Meyer&&) = delete;

		static Singleton_Meyer &Init(){
			static Singleton_Meyer single;
			return single;
		}		
	private:
		Singleton_Meyer() {}
		~Singleton_Meyer() {}

}

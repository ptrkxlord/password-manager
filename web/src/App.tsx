import { useState, useEffect, useCallback } from 'react';
import { motion, useSpring, useMotionValue } from 'framer-motion';
import { Lock, Activity, BarChart3, PieChart as PieChartIcon, ShieldCheck, Database, ArrowRight } from 'lucide-react';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  BarElement,
  ArcElement,
  Title,
  Tooltip,
  Legend,
  Filler
} from 'chart.js';
import { Line, Pie } from 'react-chartjs-2';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  BarElement,
  ArcElement,
  Title,
  Tooltip,
  Legend,
  Filler
);

function App() {
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  const [activeTab, setActiveTab] = useState('dashboard');

  const mouseX = useMotionValue(0);
  const mouseY = useMotionValue(0);
  const springConfig = { damping: 50, stiffness: 200 };
  const glowX = useSpring(mouseX, springConfig);
  const glowY = useSpring(mouseY, springConfig);

  const handleMouseMove = useCallback((e: MouseEvent) => {
    mouseX.set(e.clientX - 400);
    mouseY.set(e.clientY - 400);
  }, [mouseX, mouseY]);

  useEffect(() => {
    window.addEventListener('mousemove', handleMouseMove);
    return () => window.removeEventListener('mousemove', handleMouseMove);
  }, [handleMouseMove]);

  const lineData = {
    labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
    datasets: [{
      label: 'Vault Syncs',
      data: [12, 19, 3, 5, 2, 30],
      fill: true,
      borderColor: '#00f2ff',
      backgroundColor: 'rgba(0, 242, 255, 0.1)',
      tension: 0.4,
    }]
  };

  const pieData = {
    labels: ['Strong', 'Weak', 'Reused', 'Vulnerable'],
    datasets: [{
      data: [35, 10, 5, 2],
      backgroundColor: ['#00f2ff', '#9d00ff', '#ff0055', '#333'],
      borderWidth: 0,
    }]
  };

  return (
    <div className="min-h-screen relative text-white selection:bg-cyan-500/30 overflow-x-hidden">
      <div className="antigravity-bg" />
      <div className="antigravity-noise" />
      <motion.div
        className="mouse-glow"
        style={{ x: glowX, y: glowY }}
      />

      <nav className="fixed top-0 left-0 right-0 h-20 border-b border-white/5 backdrop-blur-xl z-50 px-10 flex items-center justify-between">
        <div className="flex items-center gap-4">
          <div className="flex flex-col">
            <span className="text-xl font-bold tracking-tighter bg-gradient-to-r from-cyan-400 to-blue-600 bg-clip-text text-transparent uppercase">PTRK</span>
            <span className="text-[8px] tracking-[0.4em] text-zinc-500 uppercase font-black">Security</span>
          </div>
        </div>

        {isLoggedIn && (
          <div className="flex gap-8">
            {['dashboard', 'vault', 'stats', 'settings'].map(tab => (
              <button
                key={tab}
                onClick={() => setActiveTab(tab)}
                className={`capitalize text-xs font-bold tracking-widest transition-colors ${activeTab === tab ? 'text-cyan-400' : 'text-zinc-500 hover:text-white'}`}
              >
                {tab}
              </button>
            ))}
          </div>
        )}

        <button
          onClick={() => setIsLoggedIn(!isLoggedIn)}
          className="btn-primary px-6 py-2.5 rounded-xl text-xs font-bold tracking-wider"
        >
          {isLoggedIn ? 'Operator' : 'Initialize'}
        </button>
      </nav>

      <main className="relative z-10 pt-40 pb-20 px-10 min-h-screen flex items-center justify-center">
        {!isLoggedIn ? (
          <div className="max-w-6xl w-full grid grid-cols-1 lg:grid-cols-2 gap-20 items-center">
            <div className="flex flex-col gap-10 order-2 lg:order-1">
              <pre className="text-[5px] md:text-[7px] leading-[1.2] font-mono text-cyan-400 drop-shadow-[0_0_20px_rgba(34,211,238,0.5)] select-none opacity-80">
{`
            .M#########################################N.           
          .#############################################.          
         #################################################         
        ###################################################        
       #####################################################       
      ###################*:::::::::::::*#####################      
     ###################.               .#####################     
    ###################.  .::::::::::.   .#####################    
   ####################  .############.   ######################   
  ####################   ##############.  #######################  
 ####################.  .##############.  ######################## 
#####################.  .##############.  #########################
#####################.   *############*   #########################
#####################.    .::::::::::.    #########################
#####################.                    #########################
######################.                  ##########################
#######################.                ###########################
########################*::::::::::::::*###########################
###################################################################
###################################################################
`}
              </pre>
              
              <div className="space-y-6">
                <motion.h1 
                  initial={{ opacity: 0, x: -30 }}
                  animate={{ opacity: 1, x: 0 }}
                  className="text-6xl font-extrabold tracking-tighter text-white leading-[1.05]"
                >
                  Control Your <span className="bg-gradient-to-r from-cyan-400 to-blue-500 bg-clip-text text-transparent italic">Identity</span> <br/>
                  with Precision.
                </motion.h1>
                <p className="text-lg text-zinc-400 max-w-md leading-relaxed">
                  The ultimate command center for ptkxlord manager. Monitor breaches, sync vaults, and manage your security from anywhere.
                </p>
              </div>
            </div>

            <motion.div 
              initial={{ opacity: 0, y: 30 }}
              animate={{ opacity: 1, y: 0 }}
              className="glass-card p-10 max-w-md w-full ml-auto order-1 lg:order-2"
            >
              <div className="space-y-8">
                <div className="space-y-2">
                  <h2 className="text-2xl font-bold text-white tracking-tight">Sign In</h2>
                  <p className="text-zinc-500 text-sm">Operator authentication required.</p>
                </div>
                
                <div className="space-y-4">
                  <div className="flex flex-col gap-2">
                    <label className="text-[10px] uppercase tracking-[0.2em] text-zinc-500 font-bold">Email Address</label>
                    <input 
                      type="email" 
                      placeholder="name@domain.com"
                      className="bg-white/5 border border-white/10 rounded-xl px-4 py-3 text-white outline-none focus:border-cyan-500/50 transition-colors"
                    />
                  </div>
                  <div className="flex flex-col gap-2">
                    <label className="text-[10px] uppercase tracking-[0.2em] text-zinc-500 font-bold">Master Password</label>
                    <div className="relative">
                      <input 
                        type="password" 
                        placeholder="••••••••"
                        className="w-full bg-white/5 border border-white/10 rounded-xl px-4 py-3 text-white outline-none focus:border-cyan-500/50 transition-colors"
                      />
                      <Lock className="absolute right-4 top-1/2 -translate-y-1/2 text-zinc-600" size={18} />
                    </div>
                  </div>
                </div>

                <div className="flex flex-col gap-4">
                  <button onClick={() => {
                    setIsLoggedIn(true);
                    const token = "mock_jwt_token_" + Math.random().toString(36).substring(7);
                    window.location.href = `http://localhost:5050/callback?token=${token}`;
                  }} className="btn-primary w-full group flex items-center justify-center gap-2">
                    Initialize Session 
                    <ArrowRight size={18} className="transition-transform group-hover:translate-x-1" />
                  </button>
                  <p className="text-center text-[10px] text-zinc-600 uppercase tracking-widest font-medium">
                    Secured by AES-256 + Argon2id
                  </p>
                </div>
              </div>
            </motion.div>
          </div>
        ) : (
          <div className="max-w-7xl w-full grid grid-cols-12 gap-8">
            <div className="col-span-12 grid grid-cols-4 gap-6">
              {[
                { label: 'Total Passwords', value: '142', icon: Lock, color: 'cyan' },
                { label: 'Security Score', value: '98%', icon: ShieldCheck, color: 'purple' },
                { label: 'Encrypted Vaults', value: '12', icon: Database, color: 'blue' },
                { label: 'Active Sessions', value: '3', icon: Activity, color: 'emerald' },
              ].map((stat, i) => (
                <motion.div 
                  key={i}
                  initial={{ opacity: 0, y: 20 }}
                  animate={{ opacity: 1, y: 0 }}
                  transition={{ delay: i * 0.1 }}
                  className="glass-card p-6 flex flex-col gap-4"
                >
                  <div className={`p-2 w-fit rounded-lg bg-white/5 border border-white/5`}>
                    <stat.icon className="text-cyan-400" size={20} />
                  </div>
                  <div className="flex flex-col gap-1">
                    <span className="text-xs text-zinc-500 font-bold uppercase tracking-wider">{stat.label}</span>
                    <span className="text-4xl font-bold tracking-tight">{stat.value}</span>
                  </div>
                </motion.div>
              ))}
            </div>

            <motion.div 
              initial={{ opacity: 0, y: 20 }}
              animate={{ opacity: 1, y: 0 }}
              transition={{ delay: 0.4 }}
              className="col-span-8 glass-card p-8"
            >
              <div className="flex items-center justify-between mb-8">
                <div className="flex items-center gap-3">
                  <BarChart3 className="text-cyan-400" />
                  <h2 className="text-lg font-bold text-white">Sync Activity</h2>
                </div>
              </div>
              <div className="h-[300px]">
                <Line data={lineData} options={{ maintainAspectRatio: false }} />
              </div>
            </motion.div>

            <motion.div 
              initial={{ opacity: 0, y: 20 }}
              animate={{ opacity: 1, y: 0 }}
              transition={{ delay: 0.5 }}
              className="col-span-4 glass-card p-8"
            >
              <div className="flex items-center gap-3 mb-8">
                <PieChartIcon className="text-purple-400" />
                <h2 className="text-lg font-bold text-white">Health Overview</h2>
              </div>
              <div className="h-[250px] flex items-center justify-center">
                <Pie data={pieData} options={{ maintainAspectRatio: false }} />
              </div>
            </motion.div>
          </div>
        )}
      </main>
    </div>
  );
}

export default App;
